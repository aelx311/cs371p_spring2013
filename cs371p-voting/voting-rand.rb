#!/usr/bin/ruby

names = ["John Doe", "Jane Smith", "Sirhan Sirhan", "John Kennedy", "Barack Obama", "LeBron James", "Glenn Downing", "George Bush", "William Powers", "Gordon Novak", "William Gates", "Steven Jobs", "Michael Scott", "Michael Dahlin", "Dirk Nowitzki", "Warren Hunt", "Andre Johnson", "Tiger Woods", "Roger Federer", "Tom Cruise"]

num_cases = rand(10) + 1 
puts num_cases.to_s + "\n\n"

for j in 0..num_cases
    num_candidates = rand(20) + 1
    puts num_candidates
    for i in 0..num_candidates - 1
        puts names[i]
    end
    num_ballots = rand(1000)
    ballots = (1..num_candidates).to_a
    for i in 0..num_ballots
        line = ''
        ballots.shuffle!
        ballots.each do |num|
           line.concat(num.to_s + ' ')
        end
        puts line
    end
    puts "\n"
end
