#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <cmath>

enum Register {
    a,
    b,
    c
};

template <typename S>
std::ostream &operator << (std::ostream &os, const std::vector<S> &vector)
{
    os << "[";
    for (auto i = vector.begin(); i != vector.end() - 1; i++)
        os << *i << ", ";
    os << *(vector.end() - 1) << "]";
    return os;
}

template <typename T, typename U>
std::ostream &operator << (std::ostream &os, const std::map<T, U> &map)
{
    for (auto i : map)
        os << i.first << ": " << i.second << "\n";
    return os;
}

class Computer {

public:
    int halt;
    int instruction_ptr;
    std::map<Register, int> registers;
    std::vector<int> program;
    std::vector<int> output;
    std::map<int, std::function<void(Computer *c)>> instructions;

    Computer(int a_initial, int b_initial, int c_initial, std::vector<int> program)
    {
        this->registers[a] = a_initial;
        this->registers[b] = b_initial;
        this->registers[c] = c_initial;
        this->program = program;
        this->instruction_ptr = 0;
        this->halt = false;
        this->output = {};
    }

    void insertInstruction(int opcode, std::function<void(Computer *c)> instruction)
    {
        this->instructions[opcode] = instruction;
    }

    int getComboValue(int operand)
    {
        if (operand >= 0 && operand <= 3)
            return (operand);
        if (operand == 4)
            return (this->registers[a]);
        if (operand == 5)
            return (this->registers[b]);
        if (operand == 6)
            return (this->registers[c]);

        throw std::invalid_argument("Invalid operand");
    }

    void runProgram()
    {
        while (!this->halt)
        {
            this->printStatus();
            int curr_opcode = this->program[this->instruction_ptr];
            std::cout << "Calling instruction " << curr_opcode << std::endl;
            this->instructions[curr_opcode](this);
            if (this->instruction_ptr >= (int)this->program.size())
                this->halt = true;
        }
    }

    void printStatus()
    {
        std::cout << "Registers:\n" << this->registers << std::endl;
        std::cout << "Halted: " << this->halt << std::endl;
        if (!this->halt)
            std::cout << "Instruction ptr at pos " << this->instruction_ptr 
                      << " with value " << this->program[this->instruction_ptr] << std::endl;
        std::cout << "Program: " << this->program << std::endl;
        if (!this->output.empty())
            std::cout << "Output: " << this->output << std::endl;
    }
};

void adv(Computer *comp) {
    int numerator = comp->registers[a];
    int denominator = std::pow(2, comp->getComboValue(comp->program[comp->instruction_ptr + 1]));
    comp->registers[a] = numerator / denominator;
    comp->instruction_ptr += 2;
}

void bxl(Computer *comp) {
    comp->registers[b] = comp->registers[b] ^ comp->program[comp->instruction_ptr + 1];
    comp->instruction_ptr += 2;
}

void bst(Computer *comp) {
    comp->registers[b] = comp->getComboValue(comp->program[comp->instruction_ptr + 1]) % 8;
    comp->instruction_ptr += 2;
}

void jnz(Computer *comp) {
    if (comp->registers[a] != 0)
        comp->instruction_ptr = comp->program[comp->instruction_ptr + 1]; // literal
    else
        comp->instruction_ptr += 2;
}

void bxc(Computer *comp) {
    comp->registers[b] = comp->registers[b] ^ comp->registers[c];
    comp->instruction_ptr += 2;
}

void out(Computer *comp) {
    comp->output.push_back(comp->getComboValue(comp->program[comp->instruction_ptr + 1]) % 8);
    comp->instruction_ptr += 2;
}

void bdv(Computer *comp) {
    int numerator = comp->registers[a];
    int denominator = std::pow(2, comp->getComboValue(comp->program[comp->instruction_ptr + 1]));
    comp->registers[b] = numerator / denominator;
    comp->instruction_ptr += 2;
}

void cdv(Computer *comp) {
    int numerator = comp->registers[a];
    int denominator = std::pow(2, comp->getComboValue(comp->program[comp->instruction_ptr + 1]));
    comp->registers[c] = numerator / denominator;
    comp->instruction_ptr += 2;
}

int main() {
    
	std::string filename("input.txt");
	std::fstream data(filename, std::fstream::in);
	std::string line;

	if (!data.is_open())
		return -1;

	int a = 0, b = 0, c = 0;
	std::vector<int> prog;

	std::getline(data, line);
	a = std::stoi(line.substr(line.find(":") + 2));
	std::getline(data, line);
	b = std::stoi(line.substr(line.find(":") + 2));
	std::getline(data, line);
	c = std::stoi(line.substr(line.find(":") + 2));

	std::getline(data, line);
	std::getline(data, line);

	std::stringstream ss(line.substr(line.find(":") + 2));
	std::string num;

	while (std::getline(ss, num, ','))
		prog.push_back(std::stoi(num));

	Computer comp(a, b, c, prog);
	comp.insertInstruction(0, adv);
	comp.insertInstruction(1, bxl);
	comp.insertInstruction(2, bst);
	comp.insertInstruction(3, jnz);
	comp.insertInstruction(4, bxc);
	comp.insertInstruction(5, out);
	comp.insertInstruction(6, bdv);
	comp.insertInstruction(7, cdv);

	comp.printStatus();
	comp.runProgram();
	comp.printStatus();

	for (auto it = comp.output.begin(); it != comp.output.end() - 1; it++)
		std::cout << *it << ",";
	
	std::cout << *(comp.output.end() - 1) << std::endl;

	return 0; 
}
