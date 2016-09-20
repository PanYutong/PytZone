BEGIN_BATCH(1 + nr_elements * 2);
OUT_BATCH((_3DSTATE_VERTEX_ELEMENTS << 16) | (2 * nr_elements - 1));
for (unsigned i = 0; i < brw->vb.nr_enabled; i++) {
  struct brw_vertex_element *input = brw->vb.enabled[i];
  uint32_t format = brw_get_vertex_surface_type(brw, input->glarray);
  uint32_t comp0 = BRW_VE1_COMPONENT_STORE_SRC;
  uint32_t comp1 = BRW_VE1_COMPONENT_STORE_SRC;
  uint32_t comp2 = BRW_VE1_COMPONENT_STORE_SRC;
  uint32_t comp3 = BRW_VE1_COMPONENT_STORE_SRC;

  switch (input->glarray->Size) {
    case 0: comp0 = BRW_VE1_COMPONENT_STORE_0;
    case 1: comp1 = BRW_VE1_COMPONENT_STORE_0;
    case 2: comp2 = BRW_VE1_COMPONENT_STORE_0;
    case 3: comp3 = input->glarray->Integer ? BRW_VE1_COMPONENT_STORE_1_INT
            : BRW_VE1_COMPONENT_STORE_1_FLT;
            break; 
  } 

  OUT_BATCH((input->buffer << GEN6_VE0_INDEX_SHIFT) |
            GEN6_VE0_VALID |
            (format << BRW_VE0_FORMAT_SHIFT) |
            (input->offset << BRW_VE0_SRC_OFFSET_SHIFT));

  OUT_BATCH((comp0 << BRW_VE1_COMPONENT_0_SHIFT) |
            (comp1 << BRW_VE1_COMPONENT_1_SHIFT) |
            (comp2 << BRW_VE1_COMPONENT_2_SHIFT) |
            (comp3 << BRW_VE1_COMPONENT_3_SHIFT));
}

unsigned vs_size = MAX2(brw->vs.prog_data->base.urb_entry_size, 1);
unsigned vs_entry_size_bytes = vs_size * 64;
...
unsigned vs_wants =
ALIGN(brw->urb.max_vs_entries * vs_entry_size_bytes,
      chunk_size_bytes) / chunk_size_bytes - vs_chunks;

count = _mesa_bitcount_64(vs_prog_data->inputs_read);
unsigned vue_entries =
MAX2(count, vs_prog_data->base.vue_map.num_slots);

vs_prog_data->base.urb_entry_size = ALIGN(vue_entries, 4) / 4;

/* For Modern GENs the PTEs and register space are split in the BAR */
gtt_phys_addr = pci_resource_start(dev->pdev, 0) +
(pci_resource_len(dev->pdev, 0) / 2);

dev_priv->gtt.gsm = ioremap_wc(gtt_phys_addr, gtt_size);
