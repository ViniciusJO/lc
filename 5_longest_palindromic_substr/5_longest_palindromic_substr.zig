const std = @import("std");

fn findMedianSortedArrays(alloc: std.mem.Allocator, nums1: []const i32, nums2: []const i32) !f64 {
    const new_size = nums1.len + nums2.len;
    const low_mid_index = new_size / 2;

    var new_array = try alloc.alloc(i32, new_size);
    defer alloc.free(new_array);
    var it1: usize = 0;
    var it2: usize = 0;

    for(0..new_size) |i| {
        if(it1 == nums1.len or (it2 < nums2.len and nums2[it2] < nums1[it1])) {
            new_array[i] = nums2[it2];
            it2 += 1;
        } else {
            new_array[i] = nums1[it1];
            it1 += 1;
        }
    }

    return if(new_size % 2 == 0)
        @as(f64, @floatFromInt(new_array[low_mid_index-1] + new_array[low_mid_index])) / 2.0
    else
        @floatFromInt(new_array[low_mid_index]);
}

test "Case 0" {
    const nums1 = [_]i32{ 1, 3 };
    const nums2 = [_]i32{ 2 };
    const expected: f32 = 2;
    const ret = try findMedianSortedArrays(std.heap.page_allocator, &nums1, &nums2);
    std.debug.print("\n\nCase0: {any}, {any} => {} ({})\n\n", .{ nums1, nums2, ret, expected });
    if(ret != expected) return error.WrongResult;
}

test "Case 1" {
    const nums1 = [_]i32{ 1, 2 };
    const nums2 = [_]i32{ 3, 4 };
    const expected: f32 = 2.5;
    const ret = try findMedianSortedArrays(std.heap.page_allocator, &nums1, &nums2);
    std.debug.print("\n\nCase1: {any}, {any} => {} ({})\n\n", .{ nums1, nums2, ret, expected });
    if(ret != expected) return error.WrongResult;
}
