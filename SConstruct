#!/usr/bin/env python
import os
import sys

from methods import print_error


libname = "PhysicsBasedAnimation"
projectdir = "project"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

# physics_anim uses exceptions
if env.get("is_msvc", False):
    env.Append(CXXFLAGS=["/EHsc"])
else:
    env.Append(CXXFLAGS=["-fexceptions"])

env.Append(CPPPATH=[
    "src/",
    "src/simulation/",
    "third_party/physics_anim/include/",
    "third_party/physics_anim/things/include/"
])

env.Append(LIBS=["tbb", "gomp"])

# Compile ONLY the solver/data files — NOT the thing_*.cpp or viewer files
import fnmatch

pba_base_sources = Glob("third_party/physics_anim/base/*.C")
# Filter out GL-dependent files
pba_base_sources = [s for s in pba_base_sources
    if not any(x in str(s) for x in ["Viewer", "ScreenCapture", "simple_viewer"])]

pba_things_sources = Glob("third_party/physics_anim/things/src/*.cpp")
# Exclude the Thing wrappers (they have GL deps) and the sim main
pba_things_sources = [s for s in pba_things_sources
    if not any(x in str(s) for x in ["thing_", "pbalitesim", "MyThing"])]

sources = Glob("src/*.cpp") + Glob("src/simulation/*.cpp")
sources += pba_base_sources + pba_things_sources


if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources,
)

copy = env.Install("{}/bin/{}/".format(projectdir, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)
