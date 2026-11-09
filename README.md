> [!WARNING]
> **Work in progress — used by the unfinished cupid port.**
>
> Shared SM8450 support is under active development and does not produce a
> bootable system on its own. Kernel panics and build failures are expected.
> Please do not open issues for them until this notice is removed.

# UniXNU SM8450 common

Shared Qualcomm SM8450 (Snapdragon 8 Gen 1, *waipio*) platform support for
[UniXNU](https://github.com/UniXNU/UniXNU). One repository serves every SM8450
board, phones included; board memory, panel, touch, firmware and partitions stay
in the board repository.

This repository is new. The upstream project ships `UniXNU-sm8550-common` only,
and SM8450 has different UFS PHY, GPU/GMU and clock-controller revisions, so the
SM8550 layer cannot be reused.

## Scope

| Path | Contents |
| --- | --- |
| `soc.toml` | SoC identity, hardware-data source and the component set |
| `configs/sm8450.config` | SoC kernel fragment (empty by design for stage 0) |
| `dts/sm8450.dtsi` | SoC resources: CPUs, PSCI, GIC, UFS, Adreno 730/GMU/SMMU |
| `kits/Sm8450Platform/GccUfs.h` | SM8450 GCC UFS clock/GDSC register facts (for the storage driver) |
| `patches/xnu`, `patches/xnu-12377` | Ordered XNU patch series for this SoC |

Values come from mainline Linux `arch/arm64/boot/dts/qcom/sm8450.dtsi` at
`f1586048fb1dabb91c82fbe11557e505587973d3`:

- 8 CPUs, MPIDR Affinity1 `0x000`-`0x700`: 4x Cortex-A510, 3x Cortex-A710,
  1x Cortex-X2; 19.2 MHz timebase.
- GICv3 distributor `0x17100000`, redistributors `0x17180000` + `0x200000`,
  `0x40000` stride.
- UFS host controller `0x1d84000` (SPI 265), QMP PHY `0x1d87000` (note: SM8550
  puts the PHY at `0x1d80000`).
- Adreno 730 `0x3d00000`, GMU `0x3d6a000`, GPU SMMU `0x3da0000`.

## Stage

`planned` -> `implemented` when a board resolves this source and the kernel
builds against it. The Adreno 730 has **no** UniXNU component yet; the DTS
nodes are present but disabled, and `CONFIG_XNU_NATIVE_ADRENO` must not be
enabled (the existing driver is Adreno 740).

## Use

```toml
[[source]]
name = "sm8450"
kind = "soc"
git = "https://github.com/<owner>/UniXNU-sm8450-common"
commit = "<40-character commit>"
```

The board sets `board.soc_source = "sm8450"`, includes `soc:dts/sm8450.dtsi`
from its own DTS, and lists `soc:patches/xnu/series` in `kernel.patch_series`.

## Verification

```sh
printf '/dts-v1/;\n/include/ "sm8450.dtsi"\n' > /tmp/sm8450.dts
   dtc -I dts -O dtb -o /tmp/sm8450.dtb -i dts /tmp/sm8450.dts
python3 -c 'import tomllib; tomllib.load(open("soc.toml","rb"))'
```

CI (`.github/workflows/dts.yml`) runs both on every push.

Released under the BSD-2-Clause-Patent License.
