#include <iostream>

class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

class PayByCard : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " via card.\n";
    }
};

class PayByCash : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " in cash.\n";
    }
};

class Order {
    PaymentStrategy* strategy = nullptr;
public:
    void setStrategy(PaymentStrategy* s) {
        if (strategy) delete strategy;
        strategy = s;
    }

    void checkout(int amount) {
        if (strategy)
            strategy->pay(amount);
        else
            std::cout << "No payment strategy selected.\n";
    }

    ~Order() {
        delete strategy;
    }
};

int main() {
    Order order;

    order.setStrategy(new PayByCard());
    order.checkout(250);

    order.setStrategy(new PayByCash());
    order.checkout(100);

    return 0;
}