#include <iostream>
#include <memory>
#include "../include/array.h"
#include "../include/utils.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    std::cout << "=== Figure Management System ===" << std::endl;
    
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Rectangle\n";
        std::cout << "2. Add Trapezoid\n";
        std::cout << "3. Add Romb\n";
        std::cout << "4. Print All Figures\n";
        std::cout << "5. Calculate Total Area\n";
        std::cout << "6. Delete Figure by Index\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose option: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                auto rect = input_rectangle<double>();
                figures.push_back(rect);
                std::cout << "Rectangle added.\n";
                break;
            }
            case 2: {
                auto trap = input_trapezoid<double>();
                figures.push_back(trap);
                std::cout << "Trapezoid added.\n";
                break;
            }
            case 3: {
                auto romb = input_romb<double>();
                figures.push_back(romb);
                std::cout << "Romb added.\n";
                break;
            }
            case 4: {
                print_all_figures(figures);
                break;
            }
            case 5: {
                double total = total_area(figures);
                std::cout << "Total area of all figures: " << total << std::endl;
                break;
            }
            case 6: {
                std::cout << "Enter index to delete: ";
                size_t index;
                std::cin >> index;
                if (index < figures.size()) {
                    figures.erase(index);
                    std::cout << "Figure at index " << index << " deleted.\n";
                } else {
                    std::cout << "Invalid index!\n";
                }
                break;
            }
            case 7: {
                std::cout << "Goodbye!\n";
                return 0;
            }
            default: {
                std::cout << "Invalid choice!\n";
                break;
            }
        }
    }
    
    return 0;
}