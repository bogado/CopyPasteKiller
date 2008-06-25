require "digest/md5"
require "src/all"

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

