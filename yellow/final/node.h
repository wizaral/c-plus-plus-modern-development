#pragma once
#include <memory>

#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    And,
    Or,
};

class Node {
public:
    virtual ~Node() = default;
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class DateComparisonNode : public Node {
    const Comparison cmp_;
    const Date date_;
public:
    DateComparisonNode(Comparison cmp, const Date &date);
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class EventComparisonNode : public Node {
    const Comparison cmp_;
    const std::string event_;
public:
    EventComparisonNode(Comparison cmp, const std::string &event);
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class LogicalOperationNode : public Node {
    const LogicalOperation operation_;
    std::shared_ptr<const Node> left_, right_;
public:
    LogicalOperationNode(LogicalOperation lop, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    bool Evaluate(const Date &date, const std::string &event) const override;
};
