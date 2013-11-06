#!/usr/bin/ruby

count = 0
while count < 1000
    puts (rand(999999) + 1).to_s + ' ' + (rand(999999) + 1).to_s
    count += 1
end
