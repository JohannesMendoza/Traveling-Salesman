/*
 * Johannes Mendoza (RK7574)
 * CS 461
 * HW 4
 * This program is intended to solve the Traveling Salesman Problem using a Genetic Algorithm
 * To run the program, follow the prompts to enter initial population size, and number of generations
 * From my personal experimentation, the best combination I could find was the sequence:
 * 6, 4, 1, 0, 3, 8, 5, 7, 2 with a total cost of 35
 * As I increased the Initial Pop and # of Gens, I found that the algorithm yielded better results
 */
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
//Function to print a vector's contents
void print_vector (vector<int> vctr){
    for (int x = 0; x < vctr.size(); x++){
        cout << vctr[x] << " ";
    }
    cout << endl;
}
//function to remove an element
vector<int> remove_vector_element(vector<int> test, int x){
    vector<int>::iterator iter = std::find(test.begin(), test.end(), x);
    swap(test[distance(test.begin(), iter)], test[test.size()-1]);
    test.pop_back();
    return test;
}
//class to represent the distance matrix from the problem
class distance_matrix{
public:
    int matrix[9][9];
    const int size = 9;
    distance_matrix(){
        matrix[0][1] = 2; matrix[0][2] = 11; matrix[0][3] = 3; matrix[0][4] = 18; matrix[0][5] = 14; matrix[0][6] = 20; matrix[0][7] = 12;matrix[0][8] = 5;
        matrix[1][2] = 13; matrix[1][3] = 10; matrix[1][4] = 5; matrix[1][5] = 3; matrix[1][6] = 8; matrix[1][7] = 20; matrix[1][8] = 17;
        matrix[2][3] = 5; matrix[2][4] = 19; matrix[2][5] = 21; matrix[2][6] = 2; matrix[2][7] = 5; matrix[2][8] = 8;
        matrix[3][4] = 6; matrix[3][5] = 4; matrix[3][6] = 12; matrix[3][7] = 15; matrix[3][8] = 1;
        matrix[4][5] = 12; matrix[4][6] = 6; matrix[4][7] = 9; matrix[4][8] = 7;
        matrix[5][6] = 19; matrix[5][7] = 7; matrix[5][8] = 4; matrix[6][7] = 21; matrix[6][8] = 13;
        matrix[7][8] = 6;
        for (int x = 0; x < size; x++){                 //for loop to fill in the inverse values of a pair of indices
            for(int y = 0; y < size; y++) {
                if (y < x){
                    matrix[x][y] = matrix[y][x];
                }
                else if (x == y)
                    matrix[x][y] = 0;
            }
        }
    }
    //function to print the matrix
    void print_matrix(){
        for (int x = 0; x < size; x++){
            for(int y = 0; y < size; y++) {
                cout << matrix[x][y] << "\t";
            }
            cout << endl;
        }
    }
    //function to calculate the cost of any sequence of traversal using this matrix
    int route (const int home, int start, vector <int> x){
        int next_index;
        if (x.size() == 0){
            cout << "0 = ";
            return matrix[start][home];
        }
        else {
            next_index = x.back();
            x.pop_back();
            if (matrix[start][next_index] != 0)
                cout << matrix[start][next_index] << " + ";
            for (int y = 0; y < x.size(); y++){
            }
            return matrix[start][next_index] + route(home, next_index, x);
        }
    }



};
//class to represent a possible travelling route
class chromosome{
public:
    vector <int> sequence;
    int cost;
    chromosome(){
        sequence = vector<int>();
        cost = 0;
    }
    chromosome(vector<int> seq, distance_matrix mat){
        sequence = seq;
        calculate_cost(mat);
    }
    void calculate_cost(distance_matrix x){
        cost = x.route(sequence.front(), sequence.front(), sequence);       //call route function from DM class
    }
    bool operator ==(const chromosome &rhs) const{              //equals operator
        if (this->sequence == rhs.sequence)
            return true;
        else
            return false;
    }
    void operator = (const chromosome &c) {                     //assignment operator
        sequence = c.sequence;
        cost = c.cost;
    }
    void print_chromosome(){
        print_vector(sequence);
    }
};
//Class to represent a population
class population{
public:
    vector<chromosome> ppulation;
    population(){

    }
    //function to create an initial population by using RNG
    void initial_population(int pop_size, distance_matrix dst){
        vector<int> cities;                             //list of cities
        chromosome temp;                                //class to hold the sequence
        int z = 0;
        for (int x = 0; x < pop_size; x++) {            //until we reach the population size
            cities = {0, 1, 2, 3, 4, 5, 6, 7, 8};       //list of cities 0-8
            while(cities.size() > 1) {                  //while cities is not empty
                z = rand() % (cities.size()-1);
                temp.sequence.push_back(cities[z]);
                cities = remove_vector_element(cities, cities[z]);
            }
            temp.sequence.push_back(cities[0]);
            if (count(ppulation.begin(), ppulation.end(), temp)) {
                x--;                                    //if the sequence was already produced (magically)
            }
            else {
                ppulation.push_back(temp);              //push the new sequence onto the population
            }
            temp.sequence.clear();                      //clear the temp sequence for new sequence
        }
    }
    void add_chromosome (vector<int> c){                //add chromosome to population
        chromosome chromo;
        chromo.sequence = c;
        ppulation.push_back(chromo);
    }
    void print_population(){
        for (int x = 0; x < ppulation.size(); x++) {
            print_vector(ppulation[x].sequence);
        }
    }
    void operator = (const population &p ) {
        ppulation = p.ppulation;
    }

};
//class to represent two chromosomes that will mate
class parents{
public:
    chromosome p1;
    chromosome p2;
    parents(){
        p1.sequence = vector<int>();
        p2.sequence = vector<int>();
    }
    void operator = (const parents &p){
        p1 = p.p1;
        p2 = p.p2;
    }
    void set_parents(chromosome x, chromosome y){
        p1 = x;
        p2 = y;
    }
    void print_parents(){
        p1.print_chromosome();
        p2.print_chromosome();
    }

};
//class to represent a pool of parents that will mate
class mating_pool{
public:
    vector<parents> pool;
    mating_pool(){
        pool = vector<parents>();
    }
    void print_mating_pool(){
        for (int x = 0; x < pool.size(); x++){
            pool[x].print_parents();
        }
    }
    void operator = (const mating_pool &p){
        pool = p.pool;
    }

};
//function that takes two sequences, a and b, and crosses them over by keeping a random subset of a, and filling out the rest
vector<int> crossover(vector<int> a, vector<int> b){
    vector<int> subset;
    vector<int> child;
    int subset_start = rand() % 6;                                  //choosing an index from 0-6 that starts the subset
    for (int x = subset_start; x < subset_start+3; x++){            //filling the subset contents
        subset.push_back(a[x]);
    }
    for (int x = 0; x < 9; x++){                                    //for the size of the sequence
        if (child.size() == subset_start){                          //when the child size reaches the index of the start of the subset
            for (int z = 0; z < subset.size(); z++) {
                child.push_back(subset[z]);                         //push back subset
            }
        }
        if (!count(subset.begin(), subset.end(), b[x])) {           //if the current\ value of b is not in the subset
            child.push_back(b[x]);                                  //push onto child
        } else;
    }
    cout << endl;                                                   //print out parents and child for debugging
    cout << "crossover starting at index: " << subset_start << endl;
    cout << "parent1: \t";
    print_vector(a);
    cout << "parent2: \t";
    print_vector(b);
    cout << "child: \t\t";
    print_vector(child);                                            //return child
    return child;
}
//function to emulate mutation by selecting two random indices and swapping them
vector<int> mutation(vector<int> x){
    int mutated_index_a = rand() % 3;
    int mutated_index_b = rand() % 2 + 5;                           //determining the indices to swap
    cout << "mutating child at indices " << mutated_index_a << " and " << mutated_index_b << endl;
    swap(x[mutated_index_a], x[mutated_index_b]);               //swap indices
    cout << "final: \t\t";
    print_vector(x);
    return x;

}
//function that takes a population, and calculates the cost of each route in the pop..
//It then groups each consecutive pair of routes as parents
// (so the best route goes with the 2nd best route, 3rd with 4th, 5th with 6th, etc..)
//
mating_pool fitness_test(population p, distance_matrix x) {
    int min = 999;
    chromosome temp;
    vector<chromosome> tempC;
    mating_pool mate_pool;

    parents par;
    int removal_index;
    cout << "calculating costs.. " << endl;                     //calculate the distance of each sequence in the population
    for (int y = 0; y < p.ppulation.size(); y++) {
        p.ppulation[y].calculate_cost(x);
        cout << p.ppulation[y].cost << endl;
    }

    tempC = p.ppulation;
    cout << "starting mating pool process with population size" << tempC.size() << endl;

    for (int a = 0; a < tempC.size(); a++) {                    //finding the minimum distance of population
        min = 999;
        for (int y = 0; y < tempC.size(); y++) {
            if (tempC[y].cost <= min) {
                min = tempC[y].cost;
                temp.sequence = tempC[y].sequence;
                removal_index = y;
            }
        }
        par.p1.sequence = temp.sequence;                        //push minimum distance sequence to parent 1
        cout << min << " for Parent 1 at " << removal_index << ": ";
        print_vector(par.p1.sequence);
        tempC.erase(tempC.begin() + removal_index);     //remove the-now-parent from population
        min = 999;
        for (int y = 0; y < tempC.size(); y++) {                //search for the new best sequence in population
            if (tempC[y].cost <= min) {
                min = tempC[y].cost;
                temp.sequence = tempC[y].sequence;
                removal_index = y;
            }
        }
        par.p2.sequence = temp.sequence;                        //push minimum distance sequence to parent 2
        tempC.erase(tempC.begin() + removal_index);
        cout << min << " for Parent 2 at " << removal_index << ": ";
        print_vector(par.p2.sequence);
        mate_pool.pool.push_back(par);                          //add parents to ,ating pool


    }
    mate_pool.print_mating_pool();
    return mate_pool;                                           //return mating pool

}
//Function that takes the above mating pool and performs crossover of the parents and mutation of the child
//child gets placed into new population
//the first pair of parents from the original mating pool also make it to the new generation
//because the first pair were the first and second best routes of the original population
population crossover_and_mutation(mating_pool mate_pool){

    cout << "Starting Crossover and Mutation with mating pool size " << mate_pool.pool.size() << endl;
    population next_generation;
    for (int x = 0; x < mate_pool.pool.size(); x++) {                           //the first set of parents will go to new population
        if (x == 0){
            next_generation.add_chromosome(mate_pool.pool[x].p1.sequence);      //add best parents to new population
            next_generation.add_chromosome(mate_pool.pool[x].p2.sequence);
        }
        next_generation.add_chromosome(mutation(crossover(mate_pool.pool[x].p1.sequence, mate_pool.pool[x].p2.sequence)));  //perform mutation and crossover
        next_generation.add_chromosome(mutation(crossover(mate_pool.pool[x].p2.sequence, mate_pool.pool[x].p1.sequence)));  //swap parents and perform mut/cross again

        cout << endl;
    }
    cout << "now returning new population of size " << next_generation.ppulation.size() << endl;
    next_generation.print_population();
    cout << endl;
    return next_generation;     //return new population10

}
//function that returns the best sequence of the latest population
chromosome get_best_sequence (population p, distance_matrix x){
    for (int y = 0; y < p.ppulation.size(); y++) {
        p.ppulation[y].calculate_cost(x);
        cout << p.ppulation[y].cost << endl;
    }
    int min = 999;
    int best_index;
    for (int y = 0; y < p.ppulation.size(); y++) {
        if (p.ppulation[y].cost <= min) {
            min = p.ppulation[y].cost;
            best_index = y;
        }
    }
    return p.ppulation[best_index];
}
//function to piece together all aspects of the genetic algorithm
void genetic_algorithm(int pop_size, int num_gen){
    distance_matrix x;
    cout << "creating initial population.." << endl;
    population p;
    p.initial_population(pop_size, x);
    p.print_population();
    for (int a = 0; a < num_gen; a++) {
        mating_pool mp = fitness_test(p, x);
        p = crossover_and_mutation(mp);
    }
    chromosome best_sequence = get_best_sequence(p, x);
    cout << "\n\n\nThe most optimal sequence found is: ";
    print_vector(best_sequence.sequence);
    cout << "The total cost for the above sequence is: ";
    cout << x.route(best_sequence.sequence.front(), best_sequence.sequence.front(), best_sequence.sequence) << endl;
    cout << "DISCLAIMER: The above addition was done in a recursive function, so addition is displayed backwards" << endl;

}
int main() {
    int size, gens;
    cout << "Enter the Size of the Initial Population: ";
    cin >> size;
    cout << "Enter the Number of Generations: ";
    cin >> gens;
    genetic_algorithm(size, gens);


    return 0;
}