const std = @import("std");

fn convert(alloc: std.mem.Allocator, s: []const u8, numRows: usize) ![]u8 {
    var ret = try alloc.alloc(u8, s.len);
    if(numRows == 1) {
        std.mem.copyForwards(u8, ret, s);
        return ret;
    }

    const base = numRows - 1;
    var count: usize = 0;

    for(0..numRows) |i| {
        var side: bool = false;
        const incs = [2]usize{ (base - i)*2, i*2 };
        var idx = i;
        while(idx < s.len) {
            ret[count] = s[idx];
            side = if(incs[0] == 0) false else if(incs[1] == 0) true else !side;
            idx += if(side) incs[0] else incs[1];
            count += 1;
        }
    }

    return ret;
}

var test_case: usize = 0;

fn test_zzc(s: []const u8, numRows: usize, expected: []const u8) !void {
    const ret = try convert(std.heap.page_allocator, s, numRows);
    std.debug.print("\n\nCase{}: \"{s}\" => \"{s}\" (\"{s}\")\n\n", .{ test_case, s, ret, expected });
    test_case += 1;
    try std.testing.expectEqualSlices(u8, expected, ret);
}

test "Case 0" { try test_zzc("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"); }

test "Case 1" { try test_zzc("PAYPALISHIRING", 4, "PINALSIGYAHRPI"); }

test "Case 2" { try test_zzc("A", 1, "A"); }

test "Case 3" { try test_zzc("PAYPALISHIRING", 1, "PAYPALISHIRING"); }
