require 'digest/md5'

module StrS
	def to_str
		return to_s()
	end
end

class SourceFile
	include StrS

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
			line = Line.new(self, num, content)
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
		return @lines[num - 1]
	end

	def ==(file)
		return false unless file.respond_to?(:filename)
		return @filename == file.filename
	end

	def to_s
		return @filename
	end
end

class Line
	include StrS
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
		line.gsub!(/\s+/, " ")
		line.gsub!(/([^a-zA-Z0-9._]) ([^a-zA-Z0-9._])/, "\1\2")

		return Digest::MD5.hexdigest(line)
	end

	def to_s
		return "#{file}:#{num}"
	end

	def ==(line)
		return false unless line.respond_to?(:key)
		return line.key == @key
	end

	def ===(line)
		return line.num == @num && line.file == @file
	end

	def next
		return @file[@num + 1]
	end

	def +(num)
		return @file[@num + num]
	end

	def -(num)
		return @file[@num - num]
	end

	def Line.[](key)
		if key.class == Line
			key = key.key
		end

		return @@allLines[key]
	end
end

class Chunk 
	include StrS
	attr :line
	attr :size

	def to_s
		return "#{line}(#{@size})"
	end

	def initialize(line, size)
		@line = line
		@size = size
	end

	def ==(chunk)
		if (size != chunk.size)
			return false
		end

		size.times do |i|
			if (line + i) != (chunk.line + i)
				return false
			end
		end
	end

	def has?(line)
		if (line.instance_of?(Array))
			line.each do |l|
				if has?(l)
					return true
				end
			end
			return false
		end

		line.file == @line.file && 
			line.num >= @line.num && line.num < (@line.num + @size)
	end

	def grow
		Chunk.new(@line, @size + 1)
	end
end

class LineCache 
	def initialize
		@lines = {}
	end

	def has?(thing)
		case thing
		when Array
			hasLines?(thing)
		when Line
			hasLine?(thing)
		else
			raise
		end
	end

	def hasLines?(lines)
		lines.each { |l| return true if hasLine?(l) }
		return false
	end

	def hasLine?(line)
		return @lines[line.to_s] == 1
	end

	def add(thing)
		case thing 
		when Chunk 
			addChunk(thing)
		when Line
			addLine(thing)
		else 
			raise 
		end
	end

	def addChunk(chunk)
		chunk.size.times do |n| 
			addLine(chunk.line + n)
		end
	end

	def addLine(line)
		@lines[line.to_s] = 1
	end
end

class LineIndexer
	def initialize
		@lines = {}
		@alllines = []
		@files = {}
	end

	def add(filename)
		@files[filename] = 
			SourceFile.new(filename) do |line|

			key = line.key

			if (@lines[key] == nil) then 
				@lines[key] = [] 
			end

			@alllines.push(line)
			@lines[key].push(line)
		end
	end

	def check(min = 2)
		result = []

		cache = LineCache.new

		n = 0
		@alllines.each do |l|
			lines = @lines[l.key]

			yield(n, @alllines.size, l) if block_given?
			n += 1;

			next if lines.size == 1

			next if cache.has?(lines)

			matches = lines.map { |line| Chunk.new(line, 1) }

			while matches.size > 1
				largerchunk = matches[0].grow

				newmatches = matches.map do |chunk|
					newchunk = chunk.grow
					if newchunk == largerchunk
						newchunk
					else
						nil
					end
				end

				newmatches.compact!

				if (newmatches.size < 2)
					matches.each { |c| cache.add(c) }
					result.push(matches) unless matches[0].size < min
				end

				matches = newmatches
			end
		end

		return result
	end
end

