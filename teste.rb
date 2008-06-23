require "line_reader"

a = LineIndexer.new
a.addSource("line_reader.rb")
a.check("line_reader.rb")
