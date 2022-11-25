# C++ Order Book Project

This project contains a skeleton project for an order book implementation that maintains a set of bid and offer orders.

## Background

An order book contains a set of bid (interests to buy) and offer (interests to sell) orders. It's canonical to organize orders by _side_ (bid or offer), then by price, into levels. Price levels are sorted by how aggressive the order is. Bids with higher prices and offers with lower prices are more aggressive.

## Example

The price of the most aggressive bid should be less than the price of the most aggressive offer, since otherwise the orders would match and produce a trade.

For example, consider 5 orders:

 - bid for 15 @ $99
 - bid for 10 @ $100
 - offer for 3 @ $103
 - offer for 12 @ $103
 - offer for 5 @ $105

They would produce an orderbook with levels as follows:

Bids:

| Price | Size |
| ----- | ---- |
| $100 | 10 |
| $99 | 15 |


Offers:

| Price | Size |
| ----- | ---- |
| $103 | 15 |
| $105 | 5 |

Note that bids are in descending order, offers are in ascending order, and the two offers @ $103 are combined onto the same price level and their sizes are added together.

## Problem

The task is to implement an orderbook that takes a series of messages that indicate new, changed, or deleted orders. 
An order is identified by a unique `order_id`. Either the price, size, or both may be changed on an order once it is placed.
Side will not change.

A change to an order is represented by a `OrderUpdate` message:

- `order_id` (string): The unique ID for this order.
- `side` (`Side`): Whether this order is a bid or an offer.
- `price` (double): The price for this order.
- `size` (double): The size for this order.
- `action` (`Action`): Whether this order is new, changed, or deleted.

The interface for the `OrderBook` class is specified:

```cpp
class OrderBook {
public:
    virtual void OnMessage(const OrderUpdate& order_update);

    virtual std::vector<PriceLevel> Bids();

    virtual std::vector<PriceLevel> Offers();

private:
};
```

## Running

To run the tests (from `cpp/order_book` dir):

* Prepare the build dir (once)
    ```shell
    $ cd cpp/order_book
    $ cmake -B build
    ```
* Build and run tests
    ```shell
    $ cmake --build build && build/order_book_test
    ```
