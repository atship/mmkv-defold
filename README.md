## Native extension mmkv for defold game engine

## Support platforms
- Windows 10
- Android 21
- iOS 16.2
- MacOSX 12.6

## Usage:

```lua
mmkv.init(sys.get_save_file("my_game", "my_mmkv")[, debug = true or false])

local db = mmkv.open('mydb'[, secret-key])
-- or
local db = mmkv.db([secret-key]) -- get the default db
-- secret-key length must <= 16 chars

mmkv.setnumber(db, 'number', 123456789.89990)
mmkv.setbool(db, 'bool', true)
mmkv.setstring(db, 'string', 'abcdefghijklmn')

mmkv.getnumber(db, 'number'[, default-number])
mmkv.getbool(db, 'bool'[, default-bool])
mmkv.getstring(db, 'string'[, default-string])

mmkv.haskey(db, 'int') -- return true or false
mmkv.remove(db, 'key') -- remove key and its value
```
