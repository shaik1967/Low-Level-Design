#include <iostream>
#include <vector>
#include <mutex>
using namespace std;

enum ProductCategory{
    Electronics,
    Clothing
};

class Product{
    public:
        string sku; //stock keeping unit
        string name;
        double price;
        int quantity;
        int threshold;
        ProductCategory category;
        class Product_Builder;
        Product(Product_Builder* builder){
            this->sku = builder->sku;
            this->name = builder->name;
            this->price = builder->price;
            this->quantity = builder->quantity;
            this->threshold = builder->threshold;
        }
        class Product_Builder{
            public:
                string sku="";
                string name="";
                double price=0.0;
                int quantity=0;
                int threshold=0;
                ProductCategory category;
                Product_Builder* setSku(string sku){
                    this->sku = sku;
                    return this;
                }
                Product_Builder* setName(string name){
                    this->name = name;
                    return this;
                }
                Product_Builder* setPrice(double price){
                    this->price = price;
                    return this;
                }
                Product_Builder* setQuantity(int quantity){
                    this->quantity = quantity;
                    return this;
                }
                Product_Builder* setThreshold(int threshold){
                    this->threshold = threshold;
                    return this;
                }
                Product_Builder* setCategory(ProductCategory category){
                    this->category = category;
                    return this;
                }
                Product* build(){
                    return new Product(this);
                }
        };

};

class ElectronicProduct: public Product{
    public:
        string brand;
        int warrantyPeriod;
        class ElectronicProduct_Builder;
        ElectronicProduct(ElectronicProduct_Builder* builder){ 
            Product(builder);
            this->brand = builder->brand;
            this->warrantyPeriod = builder->warrantyPeriod;
            this->category = ProductCategory::Electronics;
        }
        class ElectronicProduct_Builder: public Product::Product_Builder{
            public:
                string brand="";
                int warrantyPeriod=0;
                ElectronicProduct_Builder* setBrand(string brand){
                    this->brand = brand;
                    return this;
                }
                ElectronicProduct_Builder* setWarrantyPeriod(int warrantyPeriod){
                    this->warrantyPeriod = warrantyPeriod;
                    return this;
                }
                ElectronicProduct* build(){
                    return new ElectronicProduct(this);
                }
        }
};

class ClothingProduct: public Product{
    public:
        string size;
        string color;
        class ClothingProduct_Builder;
        ClothingProduct(ClothingProduct_Builder* builder){
            Product(builder);
            this->size = builder->size;
            this->color = builder->color;
            this->category = ProductCategory::Clothing;
        }
         class ClothingProduct_Builder: public Product::Product_Builder{
            public:
                string size="";
                string color="";
                ClothingProduct_Builder* setSize(string size){
                    this->size = size;
                    return this;
                }
                ClothingProduct_Builder* setColor(string color){
                    this->color = color;
                    return this;
                }
                ClothingProduct* build(){
                    return new ClothingProduct(this);
                }
        }
};


class WareHouse{
    public:
        int id;
        string name;
        string location;
        map<string,Product>products // SKU-> ID
        void addProduct(Product *p);
        void removeProduct(Product *p);
        void getAvailableQuantity(string sku);
};

class ProductFactory{
    public:
     Product *creatProduct(ProductCategory category,string sku,string name,double price, int quantity, int threshold){
        switch(category){
            case ProductCategory::Electronics:
                ElectronicProduct::ElectronicProduct_Builder *builder = new ElectronicProduct::ElectronicProduct_Builder();
                return builder->setSku(sku)->setName(name)->setPrice(price)->setQuantity(quantity)->setThreshold(threshold)->build();
            case ProductCategory::Clothing:
                ClothingProduct::ClothingProduct_Builder *builder = new ClothingProduct::ClothingProduct_Builder();
                return builder->setSku(sku)->setName(name)->setPrice(price)->setQuantity(quantity)->setThreshold(threshold)->build();
            case ProductCategory::Grocery:
                GroceryProduct::GroceryProduct_Builder *builder = new GroceryProduct::GroceryProduct_Builder();
                return builder->setSku(sku)->setName(name)->setPrice(price)->setQuantity(quantity)->setThreshold(threshold)->build();
            default:
                return nullptr;
        }
     }
};

class ProductReplenishment{
    public:
       void replenish(Product *p){
            cout<<"Not to Replenish"<<endl;
       }
};

class JustInTimeReplenishment:public ProductReplenishment{
    public:
        void replenish(Product *p){
            cout<<"Applying Just-in-Time replenishment Strategy for "<<p->name<<endl;
        }
};

class BulkOrderReplenishment:public ProductReplenishment{
    public:
        void replenish(Product *p){
            cout<<"Applying Bulk Order replenishment Strategy for "<<p->name<<endl;
        }
};

class InventoryObserver{
    public:
        virtual void update(Product *p) = 0;
};

class SupplierNotifier:public InventoryObserver{
    public:
        void update(Product *p){
            cout<<"Notifying supplier for "<<p->name<<endl;
        }
};

class DashboardAlertSystem: public InventoryObserver{
    public:
        void update(Product *p){
            double percentage=(p->quantity/p->threshold)*100;
            if(percentage < 25){
                cout<<"Alert level 4 for "<<p->name<<endl;
            }
            else if(percentage < 50){
                cout<<"Alert level 3 for "<<p->name<<endl;
            }
            else if(percentage < 75){
                cout<<"Alert level 2 for "<<p->name<<endl;
            }
            else{
                cout<<"Alert level 1 for "<<p->name<<endl;
            }
        }
};

class InventoryManager{
    static InventoryManager* instance;
    static std::mutex mtx;
    vector<WareHouse*>wareHouses;
    FVV 
    ProductReplenishment *replenishmentStrategy;
    vector<InventoryObserver*>observers;
    void checkAndReplenish(string sku);//for a single product
    void performInventoryCheck();//for all products
    public:
        InventoryManager(vector<WareHouse*>wareHouses){
            this->wareHouses=wareHouses;
            productFactory = new ProductFactory();
            replenishmentStrategy = NULL;
        }
        static InventoryManager* createInstance(){
            mtx.lock();
            if(instance == NULL){
                instance = new InventoryManager();
            }
            mtx.unlock();
            return instance;
        }
        void setReplenishmentStrategy(ProductReplenishment *strategy){
            replenishmentStrategy = strategy;
        }
};

std::mutex InventoryManager::mtx;
InventoryManager* InventoryManager::instance=NULL;

int main(){
    vector<WareHouse*>wareHouses;
    wareHouses.push_back()
    InventoryManager *manager= InventoryManager::createInstance();
    return 0;
}




