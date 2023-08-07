-- Put functions in this file to use them in several other scripts.
-- To get access to the functions, you need to put:
-- require "my_directory.my_file"
-- in any script using the functions.

local kv = {}

function kv:getint(key, def)
	return mmkv.getint(self.db, key, def)
end

function kv.open(db, key)
	local k = {}
	k.db = mmkv.open(db, key)
	setmetatable(k, {__index = kv})
	return k
end

return kv