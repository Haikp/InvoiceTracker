#pragma once

// need to be able to do alone
class invoice {
public:
    //create a task, constructor
    invoice(std::string company,
            float shipping_charge,
            float subtotal,
            float tax,
            float total,
            bool payment_status) :
        company(company),
        shipping_charge(shipping_charge),
        subtotal(subtotal),
        tax(tax),
        total(total),
        payment_status(payment_status) {}

    invoice(std::string company,
            float shipping_charge,
            float subtotal,
            bool payment_status = false) :
        company(company),
        shipping_charge(shipping_charge),
        subtotal(subtotal),
        payment_status(payment_status)
    {
        calcTax();
        calcTotal();
    }

    std::string getCompany()  const { return company;         }
    float getShippingCharge() const { return shipping_charge; }
    float getSubtotal()       const { return subtotal;        }
    float getTax()            const { return tax;             }
    float getTotal()          const { return total;           }
    bool getPaymentStatus()   const { return payment_status;  }
    void setPaymentStatus(bool status) {
        payment_status = status;
    }

private:
    std::string company   = "N/A";
    float shipping_charge = 0.00;
    float subtotal        = 0.00;
    float tax             = 0.00;
    float total           = 0.00;
    bool payment_status   = false;

    //calculate the tax and total based on info
    void calcTax(float rate = .08375) {
        tax = subtotal * rate;
    }

    void calcTotal() {
        total = shipping_charge + subtotal + tax;
    }
};
