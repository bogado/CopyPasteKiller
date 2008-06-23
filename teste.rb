require "line_reader"

a = LineIndexer.new
a.addSource("teste1")
result = a.check("teste2")

print result.join("\n")

