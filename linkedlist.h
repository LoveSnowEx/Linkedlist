#pragma once
#include <bits/stdc++.h>

template <typename T>
class Linkedlist {
private:
	struct Node {
	private:
		T data_;
		std::weak_ptr<Node> prev_;
		std::shared_ptr<Node> next_;
	public:
	
		Node() = default;
		
		Node(const T &val, std::shared_ptr<Node> prev, std::shared_ptr<Node> next) : data_(val), prev_(prev), next_(next) {}
		
		auto &data() { return data_; }
		
		auto &prev() { return prev_; }
		
		auto &next() { return next_; }
	};
	
	std::shared_ptr<Node> end_;
	
	size_t size_;
	
public:
	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		std::shared_ptr<Node> node_;
		
		iterator(std::shared_ptr<Node> node) : node_(node) {}
				
		iterator &operator++() {
			return *this = iterator(node_->next());
		}
		
		iterator operator++(int) {
			iterator tmp(this->node_);
			operator++();
			return tmp;
		}
		
		iterator &operator--() {
			return *this = iterator(node_->prev());
		}
		
		iterator operator--(int) {
			iterator tmp(this->node_);
			operator--();
			return tmp;
		}
		
		constexpr bool operator==(const iterator &rhs) {
			return node_ == rhs.node_;
		}
		
		constexpr bool operator!=(const iterator &rhs) {
			return node_ != rhs.node_;
		}
		
		T &operator*() const { return node_->data(); }
	};
	
	
	Linkedlist() : size_(0) {
		end_ = make_shared<Node>(0, nullptr, nullptr);
		end_->prev() = end_;
		end_->next() = end_;
		
	}
	
	~Linkedlist() {
		end_->prev().lock()->next() = nullptr;
		end_.reset();
	}
	
	auto size() { return size_; }
	
	auto empty() { return size_ == 0; }
	
	auto begin() { return iterator(end_->next()); }
	
	auto end() { return iterator(end_); }
	
	auto erase(iterator position) {
		if(position != end()) {
			auto prev = position.node_->prev(), next = position.node_->next();
			prev.lock()->next() = next;
			next->prev() = prev.lock();
			position++;
			size_--;
		}
		return position;
	}
	
	
	void push_front(const T &val) {
		auto tmp = make_shared<Node>(val, end_, end_->next());
		tmp->prev().lock()->next() = tmp;
		tmp->next()->prev() = tmp;
	}
	
	void push_front(T &&val) {
		auto tmp = make_shared<Node>(val, end_, end_->next());
		tmp->prev().lock()->next() = tmp;
		tmp->next()->prev() = tmp;
	}
	
	void push_back(const T &val) {
		auto tmp = make_shared<Node>(val, end_->prev().lock(), end_);
		tmp->prev().lock()->next() = tmp;
		tmp->next()->prev() = tmp;
	}
	
	void push_back(T &&val) {
		auto tmp = make_shared<Node>(val, end_->prev().lock(), end_);
		tmp->prev().lock()->next() = tmp;
		tmp->next()->prev() = tmp;
	}
};