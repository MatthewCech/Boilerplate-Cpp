-- Premake5 Wiki: https://github.com/premake/premake-core/wiki
-- Based on Premake GLFW demo courtesy of JohannesMP
-- https://github.com/JohannesMP


-- Variable definition
-- Brief reminder: This is actual lua, functions and whatnot are totally allowed.
local ROOT = "../"   -- Path to project root

-- [ WORKSPACE CONFIGURATION ] --
workspace "Boilerplate"                      -- Solution Name
    configurations { "Debug", "Release"}     -- Optimization/General config mode in VS
    platforms { "x64", "x86"}                -- Dropdown platforms section in VS
    location (ROOT .. "project_" .. _ACTION) -- Note: _ACTION is the argument passed to premake.

    -- [ PROJECT CONFIGURATION ] --
    project "Boilerplate"         -- Project name
        targetname "boilerplate"  -- Executable name
        kind "ConsoleApp"         -- Style of app in project- WindowedApp, ConsoleApp, etc.
        language "C++"

    -- [ COMPILER/LINKER CONFIG] --
    flags "FatalWarnings"  -- Warnings to 11! (all warnings on)

    -- Generate filters with info provided for Visual Studio
    filter { "platforms:*86" }
      architecture "x86"
    filter { "platforms:*64" }
      architecture "x64"

    -- Generate configs dropdown info, VS
    filter { "configurations:Debug" }
      defines { "DEBUG" }  -- Actively defined in code, can be checked for.
      flags { "Symbols" }
    filter { "configurations:Release" }
      defines { "NDEBUG" } -- Actively defined in code, can be checked for.
      optimize "On"

    filter {} -- Reset filter.

    -- [ BUILD CONFIGURATIONS ] --
    local cur_toolset = "default" -- workaround for premake issue #257

    filter {"system:macosx" } -- Mac uses clang.
      toolset "clang"
      cur_toolset = "clang"
   
    filter { "action:gmake" }
      buildoptions { "-std=c++14" }

    -- Set the rpath on the executable, to allow for relative path for dynamic lib
    filter { "system:macosx" }
      if cur_toolset == "clang" or cur_toolset == "gcc" then  
        linkoptions { "-rpath @executable_path/lib" }
      end
    
    filter {"system:windows", "action:vs*"}
      linkoptions   { "/ignore:4099" }      -- Ignore library pdb warnings when running in debug

    filter {} -- clear filter   


    -- [ FILE PATH CONFIGURATIONS ] --
    local output_dir_root         = ROOT .. "bin_%{cfg.platform}_%{cfg.buildcfg}_" .. _ACTION
    local output_dir_lib          = output_dir_root .. "/libs" -- Mac Specific
    targetdir(output_dir_root)    -- Where all output files are stored
    local source_dir_root         = ROOT .. "Source"
    local source_dir_includes     = ROOT .. "External" .. "/**/Includes"
    local source_dir_libs         = ROOT .. "External" .. "/**/" .. "Libs_" .. os.get()

    -- Files to be compiled (cpp) or added to project (visual studio)
    files
    {
      source_dir_root .. "/**.cpp",
      source_dir_root .. "/**.hpp",
      source_dir_root .. "/**.tpp",
    }

    -- Omit templates from visual studio
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}
    filter {}

    -- Ignore files for other operating systems (not necessary in this project)
    filter { "system:macosx" } removefiles { source_dir_root .. "/**_windows.*" }
    filter { "system:windows" } removefiles { source_dir_root .. "/**_macosx.*"  }
    filter {} -- reset filter

    -- Organize VS filters
    vpaths {
      ["Headers"] = 
          { 
            source_dir_root .. "**.h", 
            source_dir_root .. "**.hpp"
          },
      ["Sources/*"] = 
        {
          source_dir_root .. "**.c", 
          source_dir_root .. "**.cpp", 
          source_dir_root .. "**.tpp"
        },
      ["Docs"] = "**.txt"
    }

    -- Where compiler should look for library includes
    -- NOTE: for library headers always use  '#include <LIB/lib.hpp>' not quotes
    -- The LIB folder is an additional step to be added manually, creating an effective namespace.
    -- This prevents silly name overlapt, which we don't want to happen.
    includedirs
    {
      source_dir_includes,
      source_dir_root
    }
    

    -- Where linker should look for library files
    -- NOTE: currently each library must have "LIBS_<OS>" in its path.
    libdirs
    {
      source_dir_libs,                                           -- default: look for any libs here (does not recurse)
      source_dir_libs .. "/lib_%{cfg.platform}",                 -- libs with ONLY x32/x64 (no Release/Debug) versions
      source_dir_libs .. "/%{cfg.buildcfg}",                     -- libs with ONLY Release/Debug (no x32/x64) versions
      source_dir_libs .. "/%{cfg.buildcfg}/lib_%{cfg.platform}", -- libs with BOTH Release/Debug AND x32/x64 versions
      source_dir_libs .. "/lib_%{cfg.platform}/%{cfg.buildcfg}"  -- libs with BOTH x32/x64 AND Release/Debug versions (order reversed)
    }

    --[[
    -- OS-specific Libraries - Dynamic libs will need to be copied to output.
    -- These are the configurations for windows and mac specifically, 
    -- more can be added for linux.
    filter { "system:windows", "platforms:*86" , "configurations:Debug" }   
      links 
      { 

      }
    filter { "system:windows", "platforms:*86" , "configurations:Release" } 
      links 
      { 

      }
    filter { "system:windows", "platforms:*64" , "configurations:Debug" }   
      links 
      { 

      }
    filter { "system:windows", "platforms:*64" , "configurations:Release" } 
      links 
      { 

      }
 
      -- MAC INCLUDES, BEING DEBUG AND RELEASE. RECALL MAC IS ONLY 64-BIT
    filter { "system:macosx", "configurations:Debug" }   
      links 
      { 

      }
    filter { "system:macosx", "configurations:Release" } 
      links 
      { 

      }

    filter {} --]]
