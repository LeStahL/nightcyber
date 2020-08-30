project('nightcyber', 'cpp')

# Dependencies
qt5 = import('qt5' )
qt5Dependencies = dependency('qt5', method: 'qmake', cmake_module_path: 'C:\\Qt\\5.15.0\\msvc2019_64', modules: ['Core', 'Widgets', 'Gui', 'Multimedia', 'OpenGL'])
opengl = dependency('gl')

# Programs needed
python3 = find_program('python3')

# Globber paths
qtGlobberPath = meson.source_root() + '/meson/Qt5Globber.py'
globberPath = meson.source_root() + '/meson/Globber.py'

# Build shader verifyer
executable('scomp', meson.source_root() + '/cmake/scomp.cpp', dependencies: [opengl])
scomp = find_program(meson.build_root() + '/scomp')

# Verify all shaders
allFragmentShaderFiles = run_command(globberPath, 'frag', meson.source_root()).stdout().strip().split('\n')
verifyShadersResult = run_command(meson.build_root() + '/scomp', allFragmentShaderFiles)
message(verifyShadersResult.stdout())
    
# Build Demo
# executable(meson.project_name(), meson.source_root() + '/ls.cpp')


# Build Studio
studioPath = meson.source_root() + '/studio'
uiFiles = run_command(qtGlobberPath,'-uic',studioPath).stdout().strip().split('\n')
srcFiles = run_command(qtGlobberPath,'-src',studioPath).stdout().strip().split('\n')
uiSrcFiles = qt5.preprocess(ui_files: uiFiles, dependencies: qt5Dependencies)

cppCompiler = meson.get_compiler('cpp')
executable('studio', srcFiles, uiSrcFiles, dependencies: [qt5Dependencies, opengl])
