require "line_reader"

a = LineIndexer.new
ARGV.each do |file|
	a.add(file)
end

result = a.check(5)

result.each do |ar|
	print "#{ar.join(", ")}\n"
end
