import java.util.HashMap;
import java.util.Map;

public class Leetcode1 {
    /* LeetCode 1 两数之和 */

    /**
     * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
     * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
     * tags: 数组 哈希表
     * 示例:
     * 给定 nums = [2, 7, 11, 15], target = 9
     * 因为 nums[0] + nums[1] = 2 + 7 = 9
     * 所以返回 [0, 1]
     */
    public static void main(String[] args) {
        Solution solution = new Solution();
    }
}

class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> hashMap = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if(hashMap.containsKey(complement)) {
                return new int[] {hashMap.get(complement), i};
            }
            hashMap.put(nums[i], i);
        }
        return new int[]{};
    }
}