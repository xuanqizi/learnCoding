public class LeetCode45 {
    /* LeetCode 45 跳跃游戏 II */

    /**
     * 给定一个非负整数数组，你最初位于数组的第一个位置。
     * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
     * 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
     * 示例:
     * 输入: [2,3,1,1,4]
     * 输出: 2
     * 解释: 跳到最后一个位置的最小跳跃数是 2。
     *      从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
     * 说明:
     * 假设你总是可以到达数组的最后一个位置。
     */
    public static void main(String[] args) {
        Solution solution = new Solution();
        // solution.jump(new int[]{2, 1});
    }
}

class Solution {
    public int jump(int[] nums) {
        int count = 0;      // 记录步数
        int n = nums.length;
        int maxPos = 0;     // 当前一步能到达的最远位置
        int end = 0;        // 当前一步的结束位置
        for (int i = 0; i < n - 1; i++) {
            maxPos = Math.max(maxPos, i + nums[i]);     // 这个过程中会算出所有位置能到达的最远距离
            if(i == end) {
                end = maxPos;   // 每一步尽可能走到最远距离
                count++;
            }
        }
        return count;
    }
}
