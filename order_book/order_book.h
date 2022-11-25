#ifndef TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
#define TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

namespace order_book {


enum class Side {kBid, kOffer};

enum class Action {kNew, kChange, kDelete};

struct OrderUpdate  {
    std::string order_id;
    Side side;
    double price;
    double size;
    Action action;
};

struct PriceLevel {
    double price;
    double size;
};

class OrderBook {
public:
    virtual void OnMessage(const OrderUpdate& order_update);

    virtual std::vector<PriceLevel> Bids();

    virtual std::vector<PriceLevel> Offers();

private:
    void processBidOrder(const OrderUpdate& order_update);
    void processAskOrder(const OrderUpdate& order_update);
    
    void addBidOrder(const OrderUpdate &order_update);
    void deleteBidOrder(const OrderUpdate &order_update);

    void addAskOrder(const OrderUpdate &order_update);
    void deleteAskOrder(const OrderUpdate &order_update);
    
    unordered_map<string, OrderUpdate> orders;
    vector<PriceLevel> bids, asks;
};


}  // namespace order_book

#endif // TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
