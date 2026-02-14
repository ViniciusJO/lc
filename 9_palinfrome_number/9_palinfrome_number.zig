const std = @import("std");

fn isPalindrome_with_str(x: i32) !bool {
    const s = try std.fmt.allocPrint(std.heap.page_allocator, "{d}", .{ x });
    for(0..s.len) |i| {
        if(s[i] != s[s.len - i - 1])
            return false;
    }
    return true;
}

// #define digit_at(x,p) (x/(int)pow(10,p) % 10)
fn digit_at(x: i32, p: usize) i32 {
    return @mod(@divTrunc(x, std.math.pow(i32, 10, @intCast(p))), 10);
}
fn isPalindrome(x: i32) !bool {
  if(x < 0) return false;
  const digits: usize = @intFromFloat(std.math.log10(@as(f32, @floatFromInt(x))) + 1);
  for(0..digits) |i| {
    if(digit_at(x, i) != digit_at(x, digits - i - 1))
      return false;
  }
  return true;
}

var test_case: usize = 0;

fn test_pn(x: i32, expected: bool) !void {
    const ret = try isPalindrome(x);
    std.debug.print("\n\nCase{}: {} => {} ({})\n\n", .{ test_case, x, ret, expected });
    test_case += 1;
    try std.testing.expectEqual(expected, ret);
}


test "Case0" { try test_pn(121, true); }
test "Case1" { try test_pn(-121, false); }
test "Case2" { try test_pn(10, false); }

