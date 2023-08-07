## Native extension mmkv for defold game engine

## Support platforms
- Windows 10
- Android 21
- iOS
- MacOSX

## Usage:

```lua
mmkv.init(sys.get_save_file("my_game", "my_mmkv"))

local db = mmkv.open('mydb', secret-key) -- or db = mmkv.db(secret-key), the default db, secret-key length must <= 16 chars

mmkv.setint(db, 'int', 320)
mmkv.setnumber(db, 'number', 123456789.89990)
mmkv.setbool(db, 'bool', true)
mmkv.setstring(db, 'string', 'abcdefghijklmn')

mmkv.getint(db, 'int'[, default-int])
mmkv.getnumber(db, 'number'[, default-number])
mmkv.getbool(db, 'bool'[, default-bool])
mmkv.getstring(db, 'string'[, default-string])

mmkv.haskey(db, 'int') -- return true or false
mmkv.remove(db, 'key') -- remove key and its value
```