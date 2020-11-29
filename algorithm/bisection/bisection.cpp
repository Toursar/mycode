#include <iostream>
#include <vector>

// 一般的二分查找，最左二分，最右二分
class bisection {
public:
    // 定义一个枚举，外界传入判断需要进行的二分类型
    enum search_type
    {
        standard = 0, leftmost, rightmost
    };

    void find(std::vector<int>& nums, int target, int strategy) {
        int m = nums.size();
        if (strategy == standard)
            findnum(nums, 0, nums.size() - 1, target);
        else if (strategy == leftmost)
            findleftnum(nums, 0, nums.size() - 1, target);
        else if (strategy == rightmost) {
            findrightnum(nums, 0, nums.size() - 1, target);
        } else {
            std::cout << "strategy error\n";
        }
    }

    // 正常的二分操作
    void findnum(std::vector<int>& nums, int left, int right, int target) {
        if (left > right)
            return;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid + 1;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                std::cout << "find " << target << " at nums[" << mid << "]" << std::endl;
                return;
            }
        }
        std::cout << "can not find " << target << " in nums\n";
        std::cout << target << " should between nums[" << right << "] and [" << left << "]\n";
    }

    // 最左二分查找
    void findleftnum(std::vector<int>& nums, int left, int right, int target) {
        if (left > right)
            return;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid  + 1;
            } else if (target < nums[mid]) {
                right = mid;
            } else {
                right = mid;
            }
        }
        if (nums[left] == target)
            std::cout << "find the leftmost " << target << " at nums[" << left << "]" << std::endl;
        else if (left == nums.size() - 1) {
            std::cout << "can not find " << target << " in nums\n";
            std::cout << target << " should between nums[" << left << "] and [" << left + 1 << "]\n";
        } else {
            std::cout << "can not find " << target << " in nums\n";
            std::cout << target << " should between nums[" << left - 1 << "] and [" << left << "]\n";
        }
    }

    // 最右二分查找
    void findrightnum(std::vector<int>& nums, int left, int right, int target) {
        if (left > right)
            return;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid + 1;
            } else if (target < nums[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        // 最右二分需要进行的额外操作
        left -= 1;
        if (nums[left] == target)
            std::cout << "find the rightmost " << target << " at nums[" << left << "]" << std::endl;
        else if (left == 0) {
            std::cout << "can not find " << target << " in nums\n";
            std::cout << target << " should between nums[" << left - 1 << "] and [" << left << "]\n";
        } else {
            std::cout << "can not find " << target << " in nums\n";
            std::cout << target << " should between nums[" << left << "] and [" << left + 1 << "]\n";
        }
    }
};

int main() {
    bisection test;
    std::vector<int> nums{1, 3, 4, 5, 7, 7, 7, 7, 8, 10, 10, 12, 14};
    // 需要在参数中传入枚举值，给定二分查找的具体方式
    test.find(nums, 0, bisection::rightmost);
}