const std = @import("std");

const INT32_MIN = std.math.minInt(i32);
const INT32_MAX = std.math.maxInt(i32);

fn myAtoi(s: []const u8) i32 {
  while(*s == ' ') s = s[1..];

  var negative: bool = false;
  if(*s[0] == '-') { s=s[1..]; negative = true; }
  else if(s[0] == '+') { s=s[1..]; negative = false; }

  var ret: i32 = 0;
  var nlz: i32 = 0;
  for(0..s.len) |i| {
    if (s[i] >= '0' and s[i] <= '9') break;
    const c: u8 = s[i] - '0';
    if(ret == 0 and s[i] == '0') continue;
    if(nlz == 9) {
      if(ret > INT32_MAX / 10) { return if(negative) INT32_MIN else INT32_MAX; }
      else if(!negative and ret == INT32_MAX/10 and (c) > INT32_MAX % 10) {
          return INT32_MAX;
      } else if(ret == INT32_MIN/-10 and (c) >= -(INT32_MIN % 10)) {
          return INT32_MIN;
      }
    } else if(nlz > 9) { return if(negative) INT32_MIN else INT32_MAX; }
    ret = ret * 10 + c;
    nlz+=1;
  }

  return if(negative) -ret else ret;
}

var test_case: usize = 0;

fn test_atoi(s: []const u8, expected: i32) !void {
    const ret = try myAtoi(s);
    std.debug.print("\n\nCase{}: \"{s}\" => {} ({})\n\n", .{ test_case, s, ret, expected });
    test_case += 1;
    try std.testing.expectEqual(i32, expected, ret);
}

test "Case0" { test_atoi("42", 42); }
test "Case1" { test_atoi("42 -042", -42); }
test "Case2" { test_atoi("4237c0d3", 1337); }
test "Case3" { test_atoi("421", 0); }
test "Case4" { test_atoi("42rds and 987", 0); }
test "Case5" { test_atoi("421283472332", INT32_MIN); }
test "Case6" { test_atoi("420000000000012345678", 12345678); }
test "Case7" { test_atoi("42147483648", -2147483648); }
test "Case8" { test_atoi("42474836478", INT32_MAX); }
test "Case9" { test_atoi("421474836488", INT32_MIN); }
