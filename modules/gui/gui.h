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
            std::cout << "(x) Display Invoices\n";
            std::cout << "(v) View Invoice\n";
            std::cout << "(d) Delete Invoice\n";
            std::cout << "(p) Set Payment Status\n";
            std::cout << "(s) Save Invoices\n";
            std::cout << "(c) Clear Invoices\n";
            std::cout << "(q) Quit\n";
            std::cout << "Select an option: ";
            std::cin >> option;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Input error. Try again.\n\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            option = std::tolower(option);
            std::cout << "\n";

            switch (option) {
                case 'n':
                    addInvoice();
                    break;
                case 'x':
                    invoices.displayAll();
                    break;
                case 'v':
                    viewInvoice();
                    break;
                case 'd':
                    deleteInvoice();
                    break;
                case 'p':
                    setPaymentStatus();
                    break;
                case 's':
                    invoices.save(filename);
                    break;
                case 'c':
                    invoices.clear();
                    break;
                case 'q':
                    std::cout << "Exiting...\n";
                    return;
                default:
                    std::cout << "Invalid input. Try again.\n\n";
                    break;
            }
        }
    }

    void addInvoice() {
        std::string company;
        float shipping_charge;
        float subtotal;
        float tax;
        float total;

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

    void viewInvoice() {
        if (invoices.size() == 0) {
            std::cout << "There are no invoices to view.\n";
            return;
        }

        int index = 0;

        while(true) {
            std::cout << "There are " << invoices.size() << " invoices.\n";
            std::cout << "Which invoice do you want to view?\n";
            std::cout << "Index Number: ";
            std::cin >> index;

            if (std::cin.fail() || index < 0 || index >= invoices.size()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n";
            invoices.view(index);
            break;
        }
    }

    void deleteInvoice() {
        if (invoices.size() == 0) {
            std::cout << "There are no invoices to view.\n";
            return;
        }

        int index = 0;

        while(true) {
            std::cout << "There are " << invoices.size() << " invoices.\n";
            std::cout << "Which invoice do you want to delete?\n";
            std::cout << "Index Number: ";
            std::cin >> index;

            if (std::cin.fail() || index < 0 || index >= invoices.size()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n";
            invoices.deleteInvoice(index);
            break;
        }
    }

    void setPaymentStatus() {
        if (invoices.size() == 0) {
            std::cout << "There are no invoices to view.\n";
            return;
        }

        int index = 0;

        while(true) {
            std::cout << "Which invoice do you want change the payment status of?\n";
            std::cout << "Index Number: ";
            std::cin >> index;

            if (std::cin.fail() || index < 0 || index >= invoices.size()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n";
            invoices.view(index);
            break;
        }

        char status;
        while(true) {
            std::cout << "Has this invoice been paid? (Y/n): ";
            std::cin >> status;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            status = std::tolower(status);

            switch (status) {
                case 'y':
                    invoices.setPaymentStatus(index, true);
                    std::cout << "Invoice index " << index
                              << " set to Paid." << "\n\n";
                    break;
                case 'n':
                    invoices.setPaymentStatus(index, false);
                    std::cout << "Invoice index " << index
                              << " set to Unresolved." << "\n\n";
                    break;
                default:
                    std::cout << "Invalid input. Try again.\n\n";
                    break;
            }

            break;
        }
    }

private:
    std::string filename;
    invoice_list invoices;
};
