const std = @import("std");

fn MAX(a: usize, b: usize) usize { return if(a > b) a else b; }

fn lengthOfLongestSubstring(s: []const u8) i32 {
  var char_pos: [256]?usize = [1]?usize{ null }**256;
  var p1: usize = 0;
  var p2: usize = 0;
  var count: usize = 0;

  while(p1 < s.len and p2  < s.len) {
    const current: usize = s[p2];
    if(char_pos[current]) |c| p1 = MAX(p1, c + 1);
    char_pos[current] = p2;
    p2 += 1;
    count = MAX(count, p2 - p1);
  }

  return @intCast(count);
}

fn test_lss(s: []const u8, expected: i32) !void {
  const result = lengthOfLongestSubstring(s);
  std.debug.print("\t\"{s}\" => {} ({})", .{ s, result, expected });
  if(result != expected) {
    std.log.err("Error: processing string \"{s}\"\n\t\texpected: {}\n\t\treceiver: {}\n\n", .{ s, expected, result });
    return error.WrongResult;
  }
}


test "case_1" {
    var asci_alphabet: [127]u8 = [1]u8{0}**127;
    _ = &asci_alphabet;
    for(&asci_alphabet, 0..) |*l, i| l.* = @intCast(i+1);
    try test_lss(&asci_alphabet, 127);
}
test "case_2" { try test_lss("abcdefghijklmnopqrstuvwxyz", 26); }
test "case_3" { try test_lss("abcabcbb", 3); }
test "case_4" { try test_lss("bbbbb", 1); }
test "case_5" { try test_lss("pwwkew", 3); }
test "case_6" { try test_lss(" ", 1); }
test "case_7" { try test_lss("abba", 2); }

