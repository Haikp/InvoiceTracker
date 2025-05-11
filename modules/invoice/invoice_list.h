#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "invoice.h"

//i think file manage should be done here, because i want to be able to
// delete manage it here, and have the .txt file as just saves.
//the problem i'm having is how i should initialize this object, which
// if i want multiple save files, which i guess wouldnt be bad, i guess
// the parameter to send in to the task_list is some credential, but
// i think i'll add that later
class invoice_list {
public:
    //read a file and parse it, csv file
    invoice_list(const std::string& filename) {
        //some credential system later or something
        std::ifstream file(filename);

        std::string line;

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string company, shipping_charge_str, subtotal_str, tax_str, total_str, completed;
            float shipping_charge, subtotal, tax, total;

            std::getline(lineStream, company, ',');
            std::getline(lineStream, shipping_charge_str, ',');
            shipping_charge = std::stof(shipping_charge_str);
            std::getline(lineStream, subtotal_str, ',');
            subtotal = std::stof(subtotal_str);
            std::getline(lineStream, tax_str, ',');
            tax = std::stof(tax_str);
            std::getline(lineStream, total_str, ',');
            total = std::stof(total_str);
            std::getline(lineStream, completed);

            bool complete_check = (completed == "1");

            invoice entry(company, shipping_charge, subtotal, tax, total, complete_check);

            add(entry);
        }
    }

    void load_from_file(const std::string& filename) {
        //some credential system later or something
        std::ifstream file(filename);

        std::string line;

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string company, shipping_charge_str, subtotal_str, tax_str, total_str, completed;
            float shipping_charge, subtotal, tax, total;

            std::getline(lineStream, company, ',');
            std::getline(lineStream, shipping_charge_str, ',');
            shipping_charge = std::stof(shipping_charge_str);
            std::getline(lineStream, subtotal_str, ',');
            subtotal = std::stof(subtotal_str);
            std::getline(lineStream, tax_str, ',');
            tax = std::stof(tax_str);
            std::getline(lineStream, total_str, ',');
            total = std::stof(total_str);
            std::getline(lineStream, completed);

            bool complete_check = (completed == "1");

            invoice entry(company, shipping_charge, subtotal, tax, total, complete_check);

            add(entry);
        }
    }

    void add(invoice entry) {
        invoices.push_back(entry);
    }

    void clear() {
        invoices.clear();
    }

    void view() {
        for (const auto& invoice : invoices) {
            std::cout << "Company: "           << invoice.getCompany()
                      << "\nShipping Charge: " << invoice.getShippingCharge()
                      << "\nSubtotal: "        << invoice.getSubtotal()
                      << "\nTax: "             << invoice.getTax()
                      << "\nTotal: "           << invoice.getTotal()
                      << "\nStatus: "          << (invoice.getPaymentStatus() ? "Paid" : "Unresolved")
                      << "\n\n";
        }
    }

    //loop through vector and store in to csv
    void save(const std::string& filename) {
        std::ofstream file(filename);

        if (file.is_open()){
            for (const auto& invoice : invoices) {
                file << invoice.getCompany() << ","
                     << invoice.getShippingCharge() << ","
                     << invoice.getSubtotal() << ","
                     << invoice.getTax() << ","
                     << invoice.getTotal() << ","
                     << (invoice.getPaymentStatus() ? "1" : "0")
                     << "\n";
            }
        }

        file.close();
    }

private:
    std::vector<invoice> invoices;
};
