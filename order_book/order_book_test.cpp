#include "order_book.h"

#include <gtest/gtest.h>

namespace order_book {


TEST(OrderBook, Empty) {
    OrderBook book;

    EXPECT_TRUE(book.Bids().empty()) << "no bids";
    EXPECT_TRUE(book.Offers().empty()) << "no offers";
}

TEST(OrderBook, OneBid) {
    OrderBook book;

    book.OnMessage({"1", Side::kBid, 100.00, 10.0, Action::kNew});

    ASSERT_EQ(book.Bids().size(), 1) << "one bid";
    EXPECT_EQ(book.Bids()[0].price, 100.0) << "first bid price";
    EXPECT_EQ(book.Bids()[0].size, 10.0) << "first bid size";
}

TEST(OrderBook, BidUpdate) {
    OrderBook book;

    book.OnMessage({"1", Side::kBid, 100.00, 10.0, Action::kNew});
    book.OnMessage({"1", Side::kBid, 100.00, 7.0, Action::kChange});

    ASSERT_EQ(book.Bids().size(), 1) << "one bid";
    EXPECT_EQ(book.Bids()[0].price, 100.00) << "first bid price";
    EXPECT_EQ(book.Bids()[0].size, 7.0) << "first bid size";

    book.OnMessage({"1", Side::kBid, 100.00, 0.0, Action::kDelete});

    EXPECT_TRUE(book.Bids().empty()) << "no bids";
}

TEST(OrderBook, MultipleBids) {
    OrderBook book;

    book.OnMessage({"1", Side::kBid, 100.00, 10.0, Action::kNew});
    book.OnMessage({"2", Side::kBid, 101.00, 7.0, Action::kNew});
    book.OnMessage({"3", Side::kBid, 100.00, 5.0, Action::kNew});

    ASSERT_EQ(book.Bids().size(), 2) << "two bids";
    EXPECT_EQ(book.Bids()[0].price, 101.0) << "first bid price";
    EXPECT_EQ(book.Bids()[0].size, 7.0) << "first bid size";
    EXPECT_EQ(book.Bids()[1].price, 100.0) << "second bid price";
    EXPECT_EQ(book.Bids()[1].size, 15.0) << "second bid size";
}

TEST(OrderBook, MultipleOffers) {
    OrderBook book;

    book.OnMessage({"1", Side::kOffer, 100.00, 10.0, Action::kNew});
    book.OnMessage({"2", Side::kOffer, 101.00, 7.0, Action::kNew});
    book.OnMessage({"3", Side::kOffer, 100.00, 5.0, Action::kNew});

    ASSERT_EQ(book.Offers().size(), 2) << "two offers";
    EXPECT_EQ(book.Offers()[0].price, 100.0) << "first offer price";
    EXPECT_EQ(book.Offers()[0].size, 15.0) << "first offer size";
    EXPECT_EQ(book.Offers()[1].price, 101.0) << "second offer price";
    EXPECT_EQ(book.Offers()[1].size, 7.0) << "second offer size";
}

TEST(OrderBook, OrderChangeDelete) {
    OrderBook book;

    book.OnMessage({"1", Side::kOffer, 100.00, 10.0, Action::kNew});
    book.OnMessage({"1", Side::kOffer, 101.00, 7.0, Action::kChange});

    ASSERT_EQ(book.Offers().size(), 1) << "one offer";
    EXPECT_EQ(book.Offers()[0].price, 101.0) << "first offer price";
    EXPECT_EQ(book.Offers()[0].size, 7.0) << "first offer size";

    book.OnMessage({"1", Side::kOffer, 0.0, 0.0, Action::kDelete});

    EXPECT_TRUE(book.Offers().empty()) << "no offers";
}


}  // namespace order_book
