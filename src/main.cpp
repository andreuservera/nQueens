#include <iostream>
#include <array>
#include <vector>
#include <random>

#include "config.h"
#include "chromosome.h"
#include "ChromosomePrinter.h"

using t_chromosome_data = std::array<size_t, N_QUEENS>;

std::mt19937 rng;
std::uniform_int_distribution<size_t> distribution(0,N_QUEENS - 1);
std::uniform_int_distribution<size_t> mutation(0, 50);


void PrintChromosome(const t_chromosome& chromosome)
{
    for (const auto& col : chromosome.data){
        std::cout << col << " ";
    }
    std::cout << "\tF: " << chromosome.fitness;
}

void PrintPopulation(const std::vector<t_chromosome>& population)
{
    size_t n_chromosome = 1;
    for (const auto& chromosome : population){
        std::cout << "gene [" << n_chromosome << "]\t";
        PrintChromosome(chromosome);
        std::cout << std::endl;
        n_chromosome++;
    }
}

static int Fitness(const t_chromosome_data& chromosome_data)
{
    int score = 0;
    for (size_t i = 0; i < N_QUEENS; i++) {
        for (size_t j = 0; j < N_QUEENS; j++) {
            if (i == j) continue;
            if (chromosome_data.at(i) == chromosome_data.at(j)) {
                score++;
                continue;
            } 
            if ( (chromosome_data.at(i)) == (chromosome_data.at(j) + (abs(i-j))) ) {
                score++;
                continue;
            }
            if ( (chromosome_data.at(i)) == (chromosome_data.at(j) - (abs(i-j))) ) {
                score++;
                continue;
            }
        }
    }

    return score/2;
}

static void Crossover(  const t_chromosome_data& parent1,
                        const t_chromosome_data& parent2,
                        t_chromosome_data& child1)
{
    for (size_t gene = 0; gene < N_QUEENS; gene++) {
        if (parent1.at(gene) == parent2.at(gene)) {
            child1.at(gene) = parent1.at(gene);
        } else {
            child1.at(gene) = distribution(rng);
        }
    }
}

static void Mutate(t_chromosome_data& chromosome_data)
{
    int index = distribution(rng);
    chromosome_data.at(index) = distribution(rng);
}

bool sortFitness(t_chromosome c1, t_chromosome c2) {
    return c1.fitness < c2.fitness;
}

int main()
{
    std::cout << "The n queens problem\n";

    std::uniform_int_distribution<size_t> distribution(0, N_QUEENS - 1);
    std::uniform_int_distribution<size_t> distribution_crossover(1,6);
    std::uniform_int_distribution<size_t> distribution_parent_pool(1, PARENT_POOL_SIZE);

    /**
     * Create a chromosome.
     * 
     * A chromosome will be a board with n queens.
     * We can represent it using a vector of n size. The
     * index represents the column of the board and the value
     * represents the row in which the current queen is placed
    */

    std::vector<t_chromosome> population;
    population.reserve(POPULATION);

    std::cout << "Generating initial population...";
    for (size_t i = 0; i < POPULATION; i++) {
        t_chromosome g;
        for (size_t queen = 0; queen < N_QUEENS; queen++) {
            g.data[queen] = distribution(rng);
        }
        population.push_back(g);
    }
    std::cout << "OK\n";

    PrintPopulation(population);

    std::cout << "Calculating fitness...";
    size_t g = 1;
    for (auto& chromosome : population) {
        chromosome.fitness = Fitness(chromosome.data);
        std::cout << "Fitness chromosome [" << g << "]\t" << chromosome.fitness << std::endl;
        g++;
    }
    std::cout << "OK\n";

    bool found = false;
    int generations = 0;
    while (!found){
        generations++;

        sort(population.begin(), population.end(), sortFitness);
        
        // Delete worst
        for (size_t i = 0; i < N_CROSSOVER; i++) {
            population.erase(population.end());
        }

        // Crossover
        for (size_t i = 0; i < N_CROSSOVER*2; i=+2) {
            int random_parent_1 = distribution_parent_pool(rng);
            int random_parent_2 = distribution_parent_pool(rng);
            t_chromosome p1 = population.at(random_parent_1);
            t_chromosome p2 = population.at(random_parent_2);
            t_chromosome c1;

            Crossover(p1.data, p2.data, c1.data);
            bool mutate = mutation(rng) == 50;
            if (mutate){
                Mutate(c1.data);
            }

            c1.fitness = Fitness(c1.data);

            if (mutate) {
                std::cout << "P1: "; PrintChromosome(p1); std::cout << std::endl;
                std::cout << "P2: "; PrintChromosome(p2); std::cout << std::endl;
                std::cout << "C1: "; PrintChromosome(c1); std::cout << std::endl;
                std::cout << "***************\n";
            }

            population.push_back(c1);
            if (c1.fitness == 0) {
                found = true;
                ChromosomePrinter(c1.data);
            }
        }
    }

    std::cout << "Generations: " << generations << std::endl;

    return 0;
}