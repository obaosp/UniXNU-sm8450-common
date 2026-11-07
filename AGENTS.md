# SoC agent guide

This repository owns shared SM8450 platform description: CPU topology, PSCI,
GIC, UFS host/PHY, GPU/GMU/SMMU register windows, SoC kernel fragments and
ordered XNU patch series. Board wiring, memory maps, firmware and partitions
belong to the board repository.

## Read first

| Task | Required reading |
| --- | --- |
| Porting | https://unixnu.com/porting/ |
| SoC support | https://unixnu.com/porting/soc-support |
| Component catalog | https://unixnu.com/reference/components |
| Kernel patches | https://unixnu.com/xnu/source-and-patches |
| arm64e | https://unixnu.com/porting/arm64e |

Read `UniXNU-sm8550-common` as the reference implementation, but verify every
value: SM8450 is a different SoC revision.

## Rules

- Every address and interrupt has an upstream or vendor source. Cite it in the
  comment next to the value; do not guess.
- Do not enable a node here. Boards enable what they consume.
- Do not add board policy (memory size, panel, touch, firmware) to this
  repository.
- GPU nodes stay disabled until an Adreno 730 component exists. Do not point
  the Adreno 740 driver at 730 registers.
- SoC patches are ordered in `patches/xnu/series` and mirrored in
  `patches/xnu-12377/series` when the context matches.
- Record each hardware fact and its evidence in the board's `porting.toml`.

## Verify

```sh
dtc -I dts -O dtb -o /tmp/sm8450.dtb dts/sm8450.dtsi
python3 -c 'import tomllib; tomllib.load(open("soc.toml","rb"))'
```

A board consumes this repository through a pinned `feeds.toml` source; a change
here is not picked up until the board's commit is bumped.
