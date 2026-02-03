const std = @import("std");

fn two_sum_naive(arr: []const i32, target: i32) ![2]i32 {
    for(0..arr.len/2+1) |i| {
        if(arr[i] > target) continue;
        for(i+1..arr.len) |j| {
            if(arr[j] > target) continue;
            if(arr[i] + arr[j] == target) return [2]i32{ @intCast(i), @intCast(j) };
        }
    }
    return error.TwoSumNotFound;
}

fn two_sum(arr: []const i32, target: i32) ![2]i32 {
    var storage: std.AutoHashMap(i32, i32) = .init(std.heap.page_allocator);
    for(0..arr.len) |i| {
        const missing = target - arr[i];
        const element = storage.get(missing);
        if(element) |e| { return [2]i32{ e, @intCast(i) }; }
        else try storage.put(arr[i], @intCast(i));
    }
    return error.TwoSumNotFound;
}

test "case 1" {
    const arr = [_]i32{ 2, 7, 11, 15 };
    const target: i32 = 9;
    const expected = [_]i32{ 0, 1 };
    const result = try two_sum(&arr, target);
    std.debug.print("\ntest_tesult: {any}\n\n", .{ result });
    try std.testing.expectEqualSlices(i32, &expected, &result);
}

test "case 2" {
    const arr = [_]i32{ 3, 2, 4 };
    const target: i32 = 6;
    const expected = [_]i32{ 1, 2 };
    const result = try two_sum(&arr, target);
    std.debug.print("\ntest_tesult: {any}\n\n", .{ result });
    try std.testing.expectEqualSlices(i32, &expected, &result);
}

test "case 3" {
    const arr = [_]i32{ 3, 3 };
    const target: i32 = 6;
    const expected = [_]i32{ 0, 1 };
    const result = try two_sum(&arr, target);
    std.debug.print("\ntest_tesult: {any}\n\n", .{ result });
    try std.testing.expectEqualSlices(i32, &expected, &result);
}

