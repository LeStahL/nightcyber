project('nightcyber', 'cpp')

cppCompiler = meson.get_compiler('cpp')

# Dependencies
qt5 = import('qt5' )
qt5Dependencies = dependency('qt5', method: 'qmake', cmake_module_path: 'C:\\Qt\\5.15.0\\msvc2019_64', modules: ['Core', 'Widgets', 'Gui', 'Multimedia', 'OpenGL'])

opengl = dependency('gl')

# Windows-specific libraries
if build_machine.system() == 'windows'
    winmm = cppCompiler.find_library('winmm')
    user32 = cppCompiler.find_library('user32')
    ucrt = cppCompiler.find_library('ucrt')
    msvcrt = cppCompiler.find_library('msvcrt')
    vcruntime = cppCompiler.find_library('vcruntime')
endif

# Programs needed
python3 = find_program('python3')
glslangValidator = find_program('glslangValidator', 'bin/glslangValidator')

# Globber paths
qtGlobberPath = 'meson/Qt5Globber.py'
globberPath = 'meson/Globber.py'

# Verify all shaders
if glslangValidator.found()
    allFragmentShaderFiles = run_command(globberPath, 'frag', meson.source_root()).stdout().strip().split('\n')
    verifyShadersResult = run_command(glslangValidator, allFragmentShaderFiles)
    message(verifyShadersResult.stdout())
endif
    
# Build Demo
# executable(meson.project_name(), meson.source_root() + '/ls.cpp')


# Build Studio
studioPath = meson.source_root() + '/studio'
uiFiles = run_command(qtGlobberPath,'-uic',studioPath).stdout().strip().split('\n')
srcFiles = run_command(qtGlobberPath,'-src',studioPath).stdout().strip().split('\n')
uiSrcFiles = qt5.preprocess(ui_files: uiFiles, dependencies: qt5Dependencies)

executable('studio', srcFiles, uiSrcFiles, dependencies: [qt5Dependencies, opengl, winmm])
