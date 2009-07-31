require "src/all"

class InvalidChunk < RuntimeError
end

class Chunk 
	include StrS
	attr :line
	attr :size

	def to_s
		return "#{line}(#{@size})"
	end

	def initialize(line, size)
		if (line + (size - 1) == nil)
			raise InvalidChunk.new("chunk invalido")
		end

		@line = line
		@size = size
	end

	def ==(chunk)
		return false unless (chunk.instance_of?(Chunk))
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
		if ((@line + @size) != nil)
			Chunk.new(@line, @size + 1)
		else
			nil
		end
	end
end


