const std = @import("std");

// int reverse(int x) {
//   int ret = 0;
//   int rem = 0;
//   for(int i = 1; i < 10; i++) {
//     rem = x % 10;
//     x = x / 10; 
//     ret = ret * 10 + rem;
//     if(x == 0) break;
//     // printf("x = %d, rem = %d, ret = %d\n", x, rem, ret);
//   }
//   if(x) {
//     if(
//       ret < INT32_MIN/10 ||
//       ret > INT32_MAX/10 ||
//       (ret == INT32_MIN/10 && x < INT32_MIN%10) ||
//       (ret == INT32_MAX/10 && x > INT32_MAX%10)
//     ) return 0;
//     ret = ret * 10 + x;
//   }
//   return ret;
// }

fn reverse(_x: i32) i32 {
    var x: i32 = _x;
    var ret: i32 = 0;
    var rem: i32 = 0;
    for(0..9) |_| {
        rem = @rem(x, 10);
        x = @divTrunc(x, 10); 
        ret = ret * 10 + rem;
        std.debug.print("x = {}, rem = {}, ret = {} ({})\n", .{ x, rem, ret, std.math.maxInt(i32)});
        if(x == 0) break;
    }

    if(x != 0) {
        const I32_MAX = std.math.maxInt(i32);
        const I32_MIN = std.math.minInt(i32);
        return if(
            ret < I32_MIN/10 or ret > I32_MAX/10 or
            (ret == I32_MIN/10 and x < @rem(I32_MIN, 10)) or
            (ret == I32_MAX/10 and x > @rem(I32_MAX, 10))
        ) 0 else ret * 10 + x;
    }
    return ret;
}

var test_case: usize = 0;

fn test_ri(x: i32, expected: i32) !void {
    const ret = reverse(x);
    std.debug.print("\n\nCase{}: {} => {} ({})\n\n", .{ test_case, x, ret, expected });
    test_case += 1;
    if(expected != ret) return error.WrongResult;
}

test "Case 0" { try test_ri(123, 321); }
test "Case 1" { try test_ri(-123, -321); }
test "Case 2" { try test_ri(120, 21); }
test "Case 3" { try test_ri(1534236469, 0); }
test "Case 4" { try test_ri(-1463847412, -2147483641); }
