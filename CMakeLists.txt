# CMake mínimo necessário
cmake_minimum_required(VERSION 3.13)

# Configuração do padrão de linguagem C/C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Definir PICO_SDK_PATH automaticamente
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Definir a placa como Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importar o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Nome do projeto (removendo caracteres especiais)
project(TafUni4Semaf C CXX ASM)

# Inicializar o SDK do Pico
pico_sdk_init()

# Adicionar o executável principal
add_executable(TafUni4Semaf TafUni4Semaf.c)

# Definir nome e versão do programa
pico_set_program_name(TafUni4Semaf "TafUni4Semaf")
pico_set_program_version(TafUni4Semaf "0.1")

# Habilitar/desabilitar saída via UART/USB
pico_enable_stdio_uart(TafUni4Semaf 1)  # Habilita UART (1 para ativar, 0 para desativar)
pico_enable_stdio_usb(TafUni4Semaf 1)   # Habilita USB (1 para ativar, 0 para desativar)

# Vincular bibliotecas padrão do Pico
target_link_libraries(TafUni4Semaf pico_stdlib)

# Incluir diretórios necessários
target_include_directories(TafUni4Semaf PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Adicionar bibliotecas específicas (Wi-Fi, Bluetooth, etc.)
target_link_libraries(TafUni4Semaf pico_cyw43_arch_none)

# Gerar arquivos de saída necessários (.uf2, .bin, etc.)
pico_add_extra_outputs(TafUni4Semaf)
