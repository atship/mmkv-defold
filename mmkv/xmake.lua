add_rules("mode.debug", "mode.release")
target('mmkv')
    set_languages('c++17')
    set_kind('static')
    add_files('**.cpp')
    add_includedirs('.')
    add_cxflags("-fPIC")
    if is_plat('windows') then
        add_defines('UNICODE', '_UNICODE')
    else
        add_defines('FORCE_POSIX')
        add_files('**.S')
        if is_arch('arm64-v8a') then
            add_asflags('-march=armv8+crypto')
        end
    end
    after_build(function (target)
        local root = "$(buildir)/lib/"
        local dirs = {
            x86 = root .. 'x86-win32/',
            x64 = root .. 'x86_64-win32/',
            ["armeabi-v7a"] = root .. 'armv7-android/',
            ['arm64-v8a'] = root .. 'arm64-android/',
            arm64 = root .. 'arm64-ios/',
            x86_64 = root .. 'x86_64-osx/',
        }
        local arch = vformat("$(arch)")
        os.cp(target:targetfile(), dirs[arch])
    end)