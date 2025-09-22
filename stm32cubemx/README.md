# nix-stm32-cube-template

STM32 Cube MXとVS Codeを用いた開発環境のテンプレート

## 使い方

1. [Determinate Nix Instaler](https://github.com/DeterminateSystems/nix-installer)でNixをインストールする
2. `nix develop`を実行する
3. `stm32cubemx`でSTM32 Cube MXを起動する
4. Cube MXでコードを生成する（ToolchainはCMakeに設定する）
5. `CMakeLists.txt`の末尾に以下のコードを追加する

```cmake
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)
```

6. `./scripts/build.bash`でビルドする
7. `./scripts/upload.bash`で`<プロジェクト名>.bin`をSTM32に書き込む

## AppArmorの無効化

Ubuntuユーザーは以下の手順でAppArmorを無効化する必要があります。

1. AppArmorサービスの自動起動を無効化

```sh
sudo systemctl disable apparmor
```

2. `/etc/default/grub`を編集して、`GRUB_CMDLINE_LINUX_DEFAULT`に`apparmor=0`を追加

例:

```grub
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash apparmor=0"
```

3. GRUBの設定を更新

```sh
sudo update-grub
```

4. 再起動
