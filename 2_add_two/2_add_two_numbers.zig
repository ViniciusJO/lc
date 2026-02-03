const std = @import("std");

const ListNode = struct {
    const Self = @This();
    val: u8,
    next: ?*Self,
    const sum_epty = Self{ .val = 0, .next = null };
    pub fn init(value: u8) Self { return Self { .val = value, .next = null }; }
    pub fn from_slice(alloc: std.mem.Allocator, values: []const u8) !*Self {
        const ret = try alloc.create(Self);
        var it: *Self = ret;
        for(values, 0..) |v, i| {
            it.val = v;
            it.next = if(i < values.len - 1) try alloc.create(Self) else null;
            if(it.next) |n| it = n;
        }
        return ret;
    }
    pub fn to_slice(self: *Self, alloc: std.mem.Allocator) ![]u8 {
        var slice_builder: std.ArrayList(u8) = .empty;
        var iterator: ?*Self = self;
        while(iterator) |it| {
            try slice_builder.append(alloc, it.val);
            iterator = it.next;
        }
        return slice_builder.items;
    }
    pub fn cmp(self: *Self, other: *Self) bool {
        var it1: ?*Self = self;
        var it2: ?*Self = other;

        while(it1 != null and it2 != null) {
            if(it1 == null or it2 == null or it1.?.val != it2.?.val)
                return false;
            it1 = it1.?.next;
            it2 = it2.?.next;
        }

        return it1 == it2;
    }
};

fn addTwoNumbers(alloc: std.mem.Allocator, l1: ?*ListNode, l2: ?*ListNode) !?*ListNode {
    if(l1 == null and l2 == null) return null;
    var it1 = l2 orelse &ListNode.sum_epty;
    var it2 = l1 orelse &ListNode.sum_epty;
    const ret = try alloc.create(ListNode);
    var constructor: *ListNode = ret;
    var carry: u8 = 0;
    while(true) {
        const sum: u8 = it1.val + it2.val + carry;
        const val: u8 = @mod(sum, 10);
        carry = sum/10;
        
        constructor.val = val;
        constructor.next = null;

        if(it1.next == null and it2.next == null) break;
        it1 = if(it1.next) |n| n else &ListNode.sum_epty;
        it2 = if(it2.next) |n| n else &ListNode.sum_epty;

        const node = try alloc.create(ListNode);
        node.next = null;
        constructor.next = node;
        constructor = if(constructor.next) |n| n else unreachable;
    }
    if(carry != 0) {
        const node = try alloc.create(ListNode);
        node.val = carry;
        node.next = null;
        constructor.next = node;
    }
    return ret;
}


fn atn_test(a1: []const u8, a2: []const u8, array_expected: []const u8) !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    // std.debug.print("addTwoNumbers\n", .{});
    const l1 = try ListNode.from_slice(allocator, a1);
    const l2 = try ListNode.from_slice(allocator, a2);
    const expected = try ListNode.from_slice(allocator, array_expected);
    const result = try addTwoNumbers(allocator, l1, l2);
    std.debug.print("l1: {} => {any}\n", .{ l1, try l1.to_slice(allocator) });
    std.debug.print("l2: {} => {any}\n", .{ l2, try l2.to_slice(allocator) });
    std.debug.print("expected: {} => {any}\n", .{ expected, try expected.to_slice(allocator) });
    if(result) |r| {
        std.debug.print("result: {} => {any}\n", .{ r, try r.to_slice(allocator) });
        if(!r.cmp(expected)) return error.WrongResult;
    } else return error.ResultNull;
    std.debug.print("\n", .{});
}

test "case1" {
    std.debug.print("\n\n", .{});

    try atn_test(
        &[_]u8{ 2, 4, 3 },
        &[_]u8{ 5, 6, 4 },
        &[_]u8{ 7, 0, 8 }
    );

    try atn_test(
        &[_]u8{ 0 },
        &[_]u8{ 0 },
        &[_]u8{ 0 }
    );

    try atn_test(
        &[_]u8{ 9, 9, 9, 9, 9, 9, 9 },
        &[_]u8{ 9, 9, 9, 9 },
        &[_]u8{ 8, 9, 9, 9, 0, 0, 0, 1 }
    );
}
