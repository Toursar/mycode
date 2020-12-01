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
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid  + 1;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                right = mid - 1;
            }
        }
        //判断边界进行输出，判断结果是否超出右边界
        left = left < nums.size() ? left : nums.size() - 1;
        if (nums[left] == target)
            std::cout << "find the leftmost " << target << " at nums[" << left << "]" << std::endl;
        else if (nums[left] < target) {
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
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid + 1;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // 最右二分需要进行的额外操作，判断left是否越界后，输出left即可
        left -= 1;
        // 进行输出
        left = left >= 0 ? left : 0;
        if (nums[left] == target)
            std::cout << "find the rightmost " << target << " at nums[" << left << "]" << std::endl;
        else if (nums[left] > target) {
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
    std::vector<int> nums{1,2,3,3,3,4,5,7,8,8,9};
    // 需要在参数中传入枚举值，给定二分查找的具体方式
    test.find(nums, 0, bisection::leftmost);
}
