require 'digest/md5'

class SourceFile
	attr_reader :filename

	def initialize(file)
		if (file.class == String) then
			@filename = file
			file = File.open(file)
		else
			@filename = file.path
		end

		num = 0
		@lines = Array.new
		file.each do |content|
			num += 1
			line = Line.new(filename, num, content)
			@lines.push(line)

			if block_given? then 
				yield(line)
			end
		end
	end

	def SourceFile.getLine(key)
		return @@allLines[key]
	end

	def each
		@lines.each { |l| yield(l) }
	end

	def [](num)
		return Line[@lines[num]]
	end
end

class Line
	@@allLines = Hash.new

	attr_accessor :file
	attr_accessor :num
	attr_accessor :key

	def initialize(file, num, content)
		@file = file
		@num = num
		@key = hash(content)
		@@allLines[@key] = content
	end
	
	def hash(line)
		return Digest::MD5.hexdigest(line)
	end

	def to_s
		return "#{file}:#{num}"
	end

	def Line.[](key)
		if key.class == Line
			key = key.key
		end

		return @@allLines[key]
	end
end

class LineIndexer
	def initialize
		@lines = {}
		@files = {}
	end

	def addSource(filename)
		@files[filename] = 
			SourceFile.new(filename) do |line|

			key = line.key

			if (@lines[key] == nil) then 
				@lines[key] = []
			end

			@lines[key].push(line)
		end
	end

	def check(filename)
		if (@files[filename] == nil)
			addSource(filename)
		end

		@files[filename].each do |line|
			if (@lines[line.key].size > 1)
				print "Repeated line : " + @lines[line.key].join(", ") + "\n"
			end
		end
	end
end

a = LineIndexer.new
a.addSource("line_reader.rb")
a.check("line_reader.rb")
