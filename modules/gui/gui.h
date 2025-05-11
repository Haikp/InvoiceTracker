#pragma once
#include <iostream>
#include <ctype.h>
#include "invoice.h"
#include "invoice_list.h"

//move loop out side of constructor

class gui {
public:
    gui(const std::string& filename) : filename(filename), invoices(filename) {}

    void displayMenu() {
        //TODO: ask for which csv to load or smth later

        while (true){
            char option;
            std::cout << "Options\n";
            std::cout << "(n) New Invoice\n";
            std::cout << "(v) View Invoices\n";
            std::cout << "(s) Save Invoices\n";
            std::cout << "(c) Clear Invoices\n";
            std::cout << "(x) Exit\n";
            std::cout << "Select an option: ";
            std::cin >> option;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Input error. Try again.\n\n";
                continue;
            }

            option = std::tolower(option);
            std::cout << "\n";

            switch (option) {
                case 'n':
                    addEntry();
                    break;
                case 's':
                    saveInvoices();
                    break;
                case 'v':
                    invoices.view();
                    break;
                case 'c':
                    invoices.clear();
                    break;
                case 'x':
                    std::cout << "Exiting...\n";
                    return;
                default:
                    std::cout << "Invalid input. Try again.\n\n";
                    break;
            }
        }
    }

    void addEntry() {
        std::string company;
        float shipping_charge;
        float subtotal;
        float tax;
        float total;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter company name: ";
        std::getline(std::cin, company);

        auto get_float = [](const std::string& prompt) -> float {
            float value;

            while (true) {
                std::cout << prompt;
                std::cin >> value;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a valid number.\n";
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return value;
                }
            }
        };

        shipping_charge = get_float("Enter shipping_charge: ");
        subtotal        = get_float("Enter subtotal: ");

        invoice entry(company,
                      shipping_charge,
                      subtotal);

        invoices.add(entry);
    }

    void saveInvoices() {
        invoices.save(filename);
    }

    void clearInvoices() {
        invoices.clear();
    }

private:
    std::string filename;
    invoice_list invoices;
};
