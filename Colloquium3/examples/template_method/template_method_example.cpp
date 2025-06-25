#include <iostream>

class ReportGenerator {
public:
    void generate() {
        fetchData();
        processData();
        exportReport();
    }

    virtual ~ReportGenerator() {}

protected:
    virtual void fetchData() = 0;
    virtual void processData() = 0;

    virtual void exportReport() {
        std::cout << "Exporting report to PDF\n";
    }
};

class SalesReport : public ReportGenerator {
protected:
    void fetchData() override {
        std::cout << "Fetching sales data\n";
    }
    void processData() override {
        std::cout << "Processing sales data\n";
    }
};

class InventoryReport : public ReportGenerator {
protected:
    void fetchData() override {
        std::cout << "Fetching inventory data\n";
    }
    void processData() override {
        std::cout << "Processing inventory data\n";
    }
    void exportReport() override {
        std::cout << "Exporting inventory report to Excel\n";
    }
};

int main() {
    ReportGenerator* sales = new SalesReport();
    ReportGenerator* inventory = new InventoryReport();

    std::cout << "\nGenerating sales report:\n";
    sales->generate();

    std::cout << "\nGenerating inventory report:\n";
    inventory->generate();

    delete sales;
    delete inventory;

    return 0;
}