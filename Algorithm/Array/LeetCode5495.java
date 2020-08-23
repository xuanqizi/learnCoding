import java.util.ArrayList;
import java.util.List;

public class LeetCode5495 {
    /* LeetCode 5495 圆形赛道上经过次数最多的扇区 */

    /**
     * 给你一个整数 n 和一个整数数组 rounds 。有一条圆形赛道由 n 个扇区组成，扇区编号从 1 到 n 。
     * 现将在这条赛道上举办一场马拉松比赛，该马拉松全程由 m 个阶段组成。
     * 其中，第 i 个阶段将会从扇区 rounds[i - 1] 开始，到扇区 rounds[i] 结束。
     * 举例来说，第 1 阶段从 rounds[0] 开始，到 rounds[1] 结束。
     * 请你以数组形式返回经过次数最多的那几个扇区，按扇区编号 升序 排列。
     * 注意，赛道按扇区编号升序逆时针形成一个圆（请参见第一个示例）。
     * 示例 1：
     * 输入：n = 4, rounds = [1,3,1,2]
     * 输出：[1,2]
     * 解释：本场马拉松比赛从扇区 1 开始。经过各个扇区的次序如下所示：
     * 1 --> 2 --> 3（阶段 1 结束）--> 4 --> 1（阶段 2 结束）--> 2（阶段 3 结束，即本场马拉松结束）
     * 其中，扇区 1 和 2 都经过了两次，它们是经过次数最多的两个扇区。扇区 3 和 4 都只经过了一次。
     * 链接: https://leetcode-cn.com/problems/most-visited-sector-in-a-circular-track/
     */
    public static void main(String[] args) {
        Solution1 solution1 = new Solution1();
        Solution solution = new Solution();
        solution1.mostVisited(4, new int[]{1, 3, 1, 2});

    }
}

// 简化解法：只需模拟最后一圈
class Solution {
    public List<Integer> mostVisited(int n, int[] rounds) {
        int m = rounds.length;
        int begin = rounds[0];
        int end = rounds[m - 1];
        List<Integer> ans = new ArrayList<>();
        if (begin <= end) {
            for (int i = begin; i <= end; i++) {
                ans.add(i);
            }
        } else {
            for (int i = 1; i <= end; i++) {
                ans.add(i);
            }
            for (int i = begin; i <= n; i++) {
                ans.add(i);
            }
        }
        return ans;
    }
}

// 解法1： 模拟整个过程
class Solution1 {
    public List<Integer> mostVisited(int n, int[] rounds) {
        int m = rounds.length;
        int[] count = new int[n + 1];
        for (int i = 0; i < m - 1; i++) {
            int begin = rounds[i];
            int end = rounds[i + 1];
            int curr = begin;
            while (curr != end) {
                count[curr]++;
                curr = (curr == n ? 1 : curr + 1);
            }
            if (i == m - 2) {
                count[end]++;
            }
        }
        int max = 0;
        List<Integer> ans = new ArrayList<>();
        for (int i = 1; i < n + 1; i++) {
            if (count[i] > max) {
                max = count[i];
                ans.clear();
                ans.add(i);
            } else if (count[i] == max) {
                ans.add(i);
            }
        }
        return ans;
    }
}