#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "invoice.h"

// TODO: delete invoice function
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

    void displayAll() {
        for (int i = 0; i < invoices.size(); i++) {
            std::cout << i << " -"
                      << "\nCompany: "         << invoices[i].getCompany()
                      << "\nShipping Charge: " << invoices[i].getShippingCharge()
                      << "\nSubtotal: "        << invoices[i].getSubtotal()
                      << "\nTax: "             << invoices[i].getTax()
                      << "\nTotal: "           << invoices[i].getTotal()
                      << "\nStatus: "          << (invoices[i].getPaymentStatus() ? "Paid" : "Unresolved")
                      << "\n\n";
        }
    }

    void view(int index) {
        std::cout << index << " -"
                  << "\nCompany: "         <<  invoices[index].getCompany()
                  << "\nShipping Charge: " <<  invoices[index].getShippingCharge()
                  << "\nSubtotal: "        <<  invoices[index].getSubtotal()
                  << "\nTax: "             <<  invoices[index].getTax()
                  << "\nTotal: "           <<  invoices[index].getTotal()
                  << "\nStatus: "          << (invoices[index].getPaymentStatus() ? "Paid" : "Unresolved")
                  << "\n\n";
    }

    void deleteInvoice(int index) {
        invoices.erase(invoices.begin() + index);
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

    void setPaymentStatus(int index, bool status) {
        invoices[index].setPaymentStatus(status);
    }

    int size() {
        return invoices.size();
    }

    invoice operator[](int index) {
        return invoices[index];
    }

private:
    std::vector<invoice> invoices;
};
