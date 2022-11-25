#include "order_book.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace order_book {

auto BidComp = [](const PriceLevel &p1, const PriceLevel &p2) {
    return p1.price > p2.price;
};

auto AskComp = [](const PriceLevel &p1, const PriceLevel &p2) {
    return p1.price < p2.price;
};

void OrderBook::addBidOrder(const OrderUpdate &order_update) {
    PriceLevel pricelevel{order_update.price, order_update.size};
    orders[order_update.order_id] = order_update;
    auto it = lower_bound(begin(bids), end(bids), pricelevel, BidComp);
    if (it != end(bids) && it->price == pricelevel.price) {
        it->size += pricelevel.size;
    } else {
        bids.insert(it, pricelevel);
    }
}

void OrderBook::deleteBidOrder(const OrderUpdate &order_update) {
    PriceLevel pricelevel{order_update.price, order_update.size};
    auto it = lower_bound(begin(bids), end(bids), pricelevel, BidComp);
    if (it != end(bids)) {
        it->size -= pricelevel.size;
        if (it->size == 0) {
            bids.erase(it);
        }
    }
    orders.erase(order_update.order_id);
}

void OrderBook::addAskOrder(const OrderUpdate &order_update) {
    PriceLevel pricelevel{order_update.price, order_update.size};
    orders[order_update.order_id] = order_update;
    auto it = lower_bound(begin(asks), end(asks), pricelevel, AskComp);
    if (it != end(asks) && it->price == pricelevel.price) {
        it->size += pricelevel.size;
    } else {
        asks.insert(it, pricelevel);
    }
}

void OrderBook::deleteAskOrder(const OrderUpdate &order_update) {
    PriceLevel pricelevel{order_update.price, order_update.size};
    auto it = lower_bound(begin(asks), end(asks), pricelevel, AskComp);
    if (it != end(asks)) {
        it->size -= pricelevel.size;
        if (it->size == 0) {
            asks.erase(it);
        }
    }
    orders.erase(order_update.order_id);
}

void OrderBook::processBidOrder(const OrderUpdate &order_update) {

    switch (order_update.action) {
    case Action::kNew:
        addBidOrder(order_update);
        break;

    case Action::kChange: {
        auto it = orders.find(order_update.order_id);
        if (it != orders.end()) {
            deleteBidOrder(it->second);
        }
        addBidOrder(order_update);
        break;
    }

    case Action::kDelete:
        auto it = orders.find(order_update.order_id);
        if (it != orders.end()) {
            deleteBidOrder(it->second);
        }
        break;
    }
}

void OrderBook::processAskOrder(const OrderUpdate &order_update) {

    switch (order_update.action) {
    case Action::kNew:
        addAskOrder(order_update);
        break;

    case Action::kChange: {
        auto it = orders.find(order_update.order_id);
        if (it != orders.end()) {
            deleteAskOrder(it->second);
        }
        addAskOrder(order_update);
        break;
    }

    case Action::kDelete:
        auto it = orders.find(order_update.order_id);
        if (it != orders.end()) {
            deleteAskOrder(it->second);
        }
        break;
    }
}

void OrderBook::OnMessage(const OrderUpdate &order_update) {
    using namespace order_book;

    switch (order_update.side) {
    case Side::kBid:
        processBidOrder(order_update);
        break;
    case Side::kOffer:
        processAskOrder(order_update);
        break;
    }
}

std::vector<PriceLevel> OrderBook::Bids() { return bids; }

std::vector<PriceLevel> OrderBook::Offers() { return asks; }

} // namespace order_book
