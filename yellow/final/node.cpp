#include "node.h"
using namespace std;

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date &date)
    : cmp_(cmp), date_(date) {}

EventComparisonNode::EventComparisonNode(Comparison cmp, const std::string &event)
    : cmp_(cmp), event_(event) {}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lop, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : operation_(lop), left_(left), right_(right) {}


bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    if (cmp_ == Comparison::Less) {
        return date_ > date;
    } else if (cmp_ == Comparison::Greater) {
        return date_ < date;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return date_ >= date;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return date_ <= date;
    } else if (cmp_ == Comparison::Equal) {
        return date_ == date;
    } else /* if (cmp_ == Comparison::NotEqual) */ {
        return date_ != date;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    if (cmp_ == Comparison::Less) {
        return event_ > event;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return event_ >= event;
    } else if (cmp_ == Comparison::Greater) {
        return event_ < event;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return event_ <= event;
    } else if (cmp_ == Comparison::Equal) {
        return event_ == event;
    } else /* if (cmp_ == Comparison::NotEqual) */ {
        return event_ != event;
    }
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if (operation_ == LogicalOperation::And) {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    } else /* if (operation_ == LogicalOperation::Or) */ {
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    }
}
