#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

namespace liqusde {

    using namespace eosio;

    const extended_symbol USDE{ symbol{"USDE", 4}, "danchortoken"_n };

    const name id = "usnliq"_n;
    const name code = "danchorsmart"_n;
    const std::string description = "USDE Liquidator";
    const extended_symbol currency = USDE;
    const std::string memo = "usdetotokens";
    const int64_t min_amount = 5'000000000;


    /**
     * parameters table
     */
    struct [[eosio::table]] record_row {
        uint64_t    key;
        uint64_t    total_dollar;
        name        pledger;
        name        bearer;
        asset       amount;
        uint64_t    burst_price;
        uint64_t    bid_price;
        uint64_t    timestamp;
        uint8_t     status;

        uint64_t primary_key() const { return key; }
    };
    typedef eosio::multi_index< "record"_n, record_row > record;


    std::pair<asset, std::string> get_liquidation_amount() {

        record recordtbl( code, code.value );
        auto itr = recordtbl.rbegin();
        if(itr != recordtbl.rend() && itr->total_dollar)
            return { asset{ static_cast<int64_t>(itr->total_dollar), USDE.get_symbol() }, std::to_string(itr->key) + "-0-0"};

        return {asset{0, USDE.get_symbol()}, ""};
    }

}