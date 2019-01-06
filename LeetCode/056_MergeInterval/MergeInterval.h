//
//  MergeInterval.h
//  LeetCode
//
//  Created by Lin Luo on 1/4/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef MergeInterval_h
#define MergeInterval_h

#include <vector>
#include <map>
#include <optional>

namespace LeetCode_056
{
    struct Interval {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}
    };

    class Solution {
    public:
        std::vector<Interval> merge(const std::vector<Interval>& intervals) {
            std::map<int, int> sorted;

            for (const auto& interval : intervals) {
                auto it = sorted.upper_bound(interval.start);
                if (it != sorted.begin()) {
                    --it; // now it points to the last interval whose start is equal or less than start
                }
                std::optional<int> newStart;
                std::optional<int> newEnd;
                if (interval.start < it->first) {
                    newStart = interval.start;
                } else if (interval.start <= it->second) {
                    newStart = it->first;
                } else {
                    newStart = interval.start;
                }
                auto nx = it;
                while (nx != sorted.end()) {
                    it = nx++;
                    if (interval.end >= it->first) {
                        if (interval.end <= it->second) {
                            newEnd = it->second;
                            sorted.erase(it);
                            break;
                        }
                        if (interval.start <= it->second) {
                            sorted.erase(it); //
                        }
                    } else {
                        newEnd = interval.end;
                        break;
                    }
                }
                if (!newEnd) {
                    newEnd = interval.end;
                }
                sorted.emplace(newStart.value(), newEnd.value());
            }

            std::vector<Interval> r;
            for (const auto& [start, end] : sorted) {
                r.emplace_back(start, end);
            }

            return r;
        }
    };}

#endif /* MergeInterval_h */
