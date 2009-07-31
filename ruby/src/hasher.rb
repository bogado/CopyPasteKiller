require "digest/md5"

class Hasher
	def hash(str)
		return Digest::MD5.hexdigest(str)
	end
end

class FilterHash
	def initialize(hash, regexp, subst = " ")
		@hash = hash
		@regexp = regexp
		@subst = subst
	end

	def hash(str)
		return @hash.hash(str.sub(@regexp, @subst))
	end
end
